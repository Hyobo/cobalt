// Copyright (c) 2006-2008 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_BASE_X509_CERTIFICATE_H_
#define NET_BASE_X509_CERTIFICATE_H_

#include <string.h>

#include <map>
#include <set>
#include <string>
#include <vector>

#include "base/ref_counted.h"
#include "base/singleton.h"
#include "base/time.h"
#include "net/base/x509_cert_types.h"
#include "testing/gtest/include/gtest/gtest_prod.h"

#if defined(OS_WIN)
#include <windows.h>
#include <wincrypt.h>
#elif defined(OS_MACOSX)
#include <CoreFoundation/CFArray.h>
#include <Security/SecBase.h>
#elif defined(USE_NSS)
// Forward declaration; real one in <cert.h>
struct CERTCertificateStr;
#endif

class Pickle;

namespace net {

class CertVerifyResult;

// X509Certificate represents an X.509 certificate used by SSL.
class X509Certificate : public base::RefCountedThreadSafe<X509Certificate> {
 public:
  // A handle to the certificate object in the underlying crypto library.
  // We assume that OSCertHandle is a pointer type on all platforms and
  // NULL is an invalid OSCertHandle.
#if defined(OS_WIN)
  typedef PCCERT_CONTEXT OSCertHandle;
#elif defined(OS_MACOSX)
  typedef SecCertificateRef OSCertHandle;
#elif defined(USE_NSS)
  typedef struct CERTCertificateStr* OSCertHandle;
#else
  // TODO(ericroman): not implemented
  typedef void* OSCertHandle;
#endif

  typedef std::vector<OSCertHandle> OSCertHandles;

  // Legacy names for types now defined in x509_cert_types.h.
  // TODO(snej): Clean up existing code using these names to use the new names.
  typedef CertPrincipal Principal;
  typedef CertPolicy Policy;
  typedef SHA1Fingerprint Fingerprint;
  typedef SHA1FingerprintLessThan FingerprintLessThan;

  // Predicate functor used in maps when X509Certificate is used as the key.
  class LessThan
      : public std::binary_function<X509Certificate*, X509Certificate*, bool> {
   public:
    bool operator() (X509Certificate* lhs,  X509Certificate* rhs) const;
  };

  // Where the certificate comes from.  The enumeration constants are
  // listed in increasing order of preference.
  enum Source {
    SOURCE_UNUSED = 0,            // The source_ member is not used.
    SOURCE_LONE_CERT_IMPORT = 1,  // From importing a certificate without
                                  // its intermediate CA certificates.
    SOURCE_FROM_NETWORK = 2,      // From the network.
  };

  enum VerifyFlags {
    VERIFY_REV_CHECKING_ENABLED = 1 << 0,
    VERIFY_EV_CERT = 1 << 1,
  };

  // Create an X509Certificate from a handle to the certificate object in the
  // underlying crypto library. |source| specifies where |cert_handle| comes
  // from.  Given two certificate handles for the same certificate, our
  // certificate cache prefers the handle from the network because our HTTP
  // cache isn't caching the corresponding intermediate CA certificates yet
  // (http://crbug.com/7065).
  // The list of intermediate certificates is ignored under NSS (i.e. Linux.)
  // The returned pointer must be stored in a scoped_refptr<X509Certificate>.
  static X509Certificate* CreateFromHandle(OSCertHandle cert_handle,
      Source source,
      const OSCertHandles& intermediates);

  // Create an X509Certificate from the BER-encoded representation.
  // Returns NULL on failure.
  //
  // The returned pointer must be stored in a scoped_refptr<X509Certificate>.
  static X509Certificate* CreateFromBytes(const char* data, int length);

  // Create an X509Certificate from the representation stored in the given
  // pickle.  The data for this object is found relative to the given
  // pickle_iter, which should be passed to the pickle's various Read* methods.
  // Returns NULL on failure.
  //
  // The returned pointer must be stored in a scoped_refptr<X509Certificate>.
  static X509Certificate* CreateFromPickle(const Pickle& pickle,
                                           void** pickle_iter);

  // Creates a X509Certificate from the ground up.  Used by tests that simulate
  // SSL connections.
  X509Certificate(const std::string& subject, const std::string& issuer,
                  base::Time start_date, base::Time expiration_date);

  // Appends a representation of this object to the given pickle.
  void Persist(Pickle* pickle);

  // The subject of the certificate.  For HTTPS server certificates, this
  // represents the web server.  The common name of the subject should match
  // the host name of the web server.
  const Principal& subject() const { return subject_; }

  // The issuer of the certificate.
  const Principal& issuer() const { return issuer_; }

  // Time period during which the certificate is valid.  More precisely, this
  // certificate is invalid before the |valid_start| date and invalid after
  // the |valid_expiry| date.
  // If we were unable to parse either date from the certificate (or if the cert
  // lacks either date), the date will be null (i.e., is_null() will be true).
  const base::Time& valid_start() const { return valid_start_; }
  const base::Time& valid_expiry() const { return valid_expiry_; }

  // The fingerprint of this certificate.
  const Fingerprint& fingerprint() const { return fingerprint_; }

  // Gets the DNS names in the certificate.  Pursuant to RFC 2818, Section 3.1
  // Server Identity, if the certificate has a subjectAltName extension of
  // type dNSName, this method gets the DNS names in that extension.
  // Otherwise, it gets the common name in the subject field.
  void GetDNSNames(std::vector<std::string>* dns_names) const;

  // Convenience method that returns whether this certificate has expired as of
  // now.
  bool HasExpired() const;

#if defined(OS_MACOSX) || defined(OS_WIN)
  // Returns intermediate certificates added via AddIntermediateCertificate().
  // Ownership follows the "get" rule: it is the caller's responsibility to
  // retain the elements of the result.
  const OSCertHandles& GetIntermediateCertificates() const {
    return intermediate_ca_certs_;
  }
#endif

  // Returns true if I already contain the given intermediate cert.
  bool HasIntermediateCertificate(OSCertHandle cert);

  // Returns true if I already contain all the given intermediate certs.
  bool HasIntermediateCertificates(const OSCertHandles& certs);

#if defined(OS_MACOSX)
  // Does this certificate's usage allow SSL client authentication?
  bool SupportsSSLClientAuth() const;

  // Do any of the given issuer names appear in this cert's chain of trust?
  bool IsIssuedBy(const std::vector<CertPrincipal>& valid_issuers);

  // Creates a security policy for SSL client certificates.
  static OSStatus CreateSSLClientPolicy(SecPolicyRef* outPolicy);

  // Adds all available SSL client identity certs to the given vector.
  // |server_domain| is a hint for which domain the cert is to be sent to
  // (a cert previously specified as the default for that domain will be given
  // precedence and returned first in the output vector.)
  // If valid_issuers is non-empty, only certs that were transitively issued by
  // one of the given names will be included in the list.
  static bool GetSSLClientCertificates(
      const std::string& server_domain,
      const std::vector<CertPrincipal>& valid_issuers,
      std::vector<scoped_refptr<X509Certificate> >* certs);

  // Creates the chain of certs to use for this client identity cert.
  CFArrayRef CreateClientCertificateChain() const;
#endif

  // Verifies the certificate against the given hostname.  Returns OK if
  // successful or an error code upon failure.
  //
  // The |*verify_result| structure, including the |verify_result->cert_status|
  // bitmask, is always filled out regardless of the return value.  If the
  // certificate has multiple errors, the corresponding status flags are set in
  // |verify_result->cert_status|, and the error code for the most serious
  // error is returned.
  //
  // |flags| is bitwise OR'd of VerifyFlags.
  // If VERIFY_REV_CHECKING_ENABLED is set in |flags|, certificate revocation
  // checking is performed.  If VERIFY_EV_CERT is set in |flags| too,
  // EV certificate verification is performed.
  int Verify(const std::string& hostname,
             int flags,
             CertVerifyResult* verify_result) const;

  OSCertHandle os_cert_handle() const { return cert_handle_; }

  // Returns true if two OSCertHandles refer to identical certificates.
  static bool IsSameOSCert(OSCertHandle a, OSCertHandle b);

  // Creates an OS certificate handle from the BER-encoded representation.
  // Returns NULL on failure.
  static OSCertHandle CreateOSCertHandleFromBytes(const char* data,
                                                  int length);

  // Duplicates (or adds a reference to) an OS certificate handle.
  static OSCertHandle DupOSCertHandle(OSCertHandle cert_handle);

  // Frees (or releases a reference to) an OS certificate handle.
  static void FreeOSCertHandle(OSCertHandle cert_handle);

 private:
  friend class base::RefCountedThreadSafe<X509Certificate>;
  FRIEND_TEST(X509CertificateTest, Cache);
  FRIEND_TEST(X509CertificateTest, IntermediateCertificates);

  // A cache of X509Certificate objects.
  class Cache {
   public:
    static Cache* GetInstance();
    void Insert(X509Certificate* cert);
    void Remove(X509Certificate* cert);
    X509Certificate* Find(const Fingerprint& fingerprint);

   private:
    typedef std::map<Fingerprint, X509Certificate*, FingerprintLessThan>
        CertMap;

    // Obtain an instance of X509Certificate::Cache via GetInstance().
    Cache() { }
    friend struct DefaultSingletonTraits<Cache>;

    // You must acquire this lock before using any private data of this object.
    // You must not block while holding this lock.
    Lock lock_;

    // The certificate cache.  You must acquire |lock_| before using |cache_|.
    CertMap cache_;

    DISALLOW_COPY_AND_ASSIGN(Cache);
  };

  // Construct an X509Certificate from a handle to the certificate object
  // in the underlying crypto library.
  X509Certificate(OSCertHandle cert_handle, Source source,
                  const OSCertHandles& intermediates);

  ~X509Certificate();

  // Common object initialization code.  Called by the constructors only.
  void Initialize();

  bool VerifyEV() const;

  // Calculates the SHA-1 fingerprint of the certificate.  Returns an empty
  // (all zero) fingerprint on failure.
  static Fingerprint CalculateFingerprint(OSCertHandle cert_handle);

  // The subject of the certificate.
  Principal subject_;

  // The issuer of the certificate.
  Principal issuer_;

  // This certificate is not valid before |valid_start_|
  base::Time valid_start_;

  // This certificate is not valid after |valid_expiry_|
  base::Time valid_expiry_;

  // The fingerprint of this certificate.
  Fingerprint fingerprint_;

  // A handle to the certificate object in the underlying crypto library.
  OSCertHandle cert_handle_;

#if defined(OS_MACOSX) || defined(OS_WIN)
  // Untrusted intermediate certificates associated with this certificate
  // that may be needed for chain building. (NSS impl does not need these.)
  OSCertHandles intermediate_ca_certs_;
#endif

#if defined(OS_MACOSX)
  // Blocks multiple threads from verifying the cert simultaneously.
  // (Marked mutable because it's used in a const method.)
  mutable Lock verification_lock_;
#endif

  // Where the certificate comes from.
  Source source_;

  DISALLOW_COPY_AND_ASSIGN(X509Certificate);
};

}  // namespace net

#endif  // NET_BASE_X509_CERTIFICATE_H_
