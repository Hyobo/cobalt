// This file was GENERATED by command:
//     pump.py optional_internal.h.pump
// DO NOT EDIT BY HAND!!!



// Begin forwarding constructor definitions ////////////////////////////////////
  explicit optional(in_place_t) {
    InitializeAsDisengaged();
    new (value_memory_.void_data()) T();
    engaged_ = true;
#if !defined(NDEBUG)
    value_ptr_ = static_cast<const T*>(value_memory_.void_data());
#endif
  }
  template <typename P1>
  explicit optional(in_place_t, const P1& p1) {
    InitializeAsDisengaged();
    new (value_memory_.void_data()) T(p1);
    engaged_ = true;
#if !defined(NDEBUG)
    value_ptr_ = static_cast<const T*>(value_memory_.void_data());
#endif
  }
  template <typename P1, typename P2>
  explicit optional(in_place_t, const P1& p1, const P2& p2) {
    InitializeAsDisengaged();
    new (value_memory_.void_data()) T(p1, p2);
    engaged_ = true;
#if !defined(NDEBUG)
    value_ptr_ = static_cast<const T*>(value_memory_.void_data());
#endif
  }
  template <typename P1, typename P2, typename P3>
  explicit optional(in_place_t, const P1& p1, const P2& p2, const P3& p3) {
    InitializeAsDisengaged();
    new (value_memory_.void_data()) T(p1, p2, p3);
    engaged_ = true;
#if !defined(NDEBUG)
    value_ptr_ = static_cast<const T*>(value_memory_.void_data());
#endif
  }
  template <typename P1, typename P2, typename P3, typename P4>
  explicit optional(in_place_t, const P1& p1, const P2& p2, const P3& p3,
      const P4& p4) {
    InitializeAsDisengaged();
    new (value_memory_.void_data()) T(p1, p2, p3, p4);
    engaged_ = true;
#if !defined(NDEBUG)
    value_ptr_ = static_cast<const T*>(value_memory_.void_data());
#endif
  }
  template <typename P1, typename P2, typename P3, typename P4, typename P5>
  explicit optional(in_place_t, const P1& p1, const P2& p2, const P3& p3,
      const P4& p4, const P5& p5) {
    InitializeAsDisengaged();
    new (value_memory_.void_data()) T(p1, p2, p3, p4, p5);
    engaged_ = true;
#if !defined(NDEBUG)
    value_ptr_ = static_cast<const T*>(value_memory_.void_data());
#endif
  }
  template <typename P1, typename P2, typename P3, typename P4, typename P5,
      typename P6>
  explicit optional(in_place_t, const P1& p1, const P2& p2, const P3& p3,
      const P4& p4, const P5& p5, const P6& p6) {
    InitializeAsDisengaged();
    new (value_memory_.void_data()) T(p1, p2, p3, p4, p5, p6);
    engaged_ = true;
#if !defined(NDEBUG)
    value_ptr_ = static_cast<const T*>(value_memory_.void_data());
#endif
  }
  template <typename P1, typename P2, typename P3, typename P4, typename P5,
      typename P6, typename P7>
  explicit optional(in_place_t, const P1& p1, const P2& p2, const P3& p3,
      const P4& p4, const P5& p5, const P6& p6, const P7& p7) {
    InitializeAsDisengaged();
    new (value_memory_.void_data()) T(p1, p2, p3, p4, p5, p6, p7);
    engaged_ = true;
#if !defined(NDEBUG)
    value_ptr_ = static_cast<const T*>(value_memory_.void_data());
#endif
  }
// End forwarding constructor definitions //////////////////////////////////////

// Begin emplace(...) definitions //////////////////////////////////////////////
  void emplace() {
    EnsureDisengaged();
    new (value_memory_.void_data()) T();
    engaged_ = true;
#if !defined(NDEBUG)
    value_ptr_ = static_cast<const T*>(value_memory_.void_data());
#endif
  }
  template <typename P1>
  void emplace(const P1& p1) {
    EnsureDisengaged();
    new (value_memory_.void_data()) T(p1);
    engaged_ = true;
#if !defined(NDEBUG)
    value_ptr_ = static_cast<const T*>(value_memory_.void_data());
#endif
  }
  template <typename P1, typename P2>
  void emplace(const P1& p1, const P2& p2) {
    EnsureDisengaged();
    new (value_memory_.void_data()) T(p1, p2);
    engaged_ = true;
#if !defined(NDEBUG)
    value_ptr_ = static_cast<const T*>(value_memory_.void_data());
#endif
  }
  template <typename P1, typename P2, typename P3>
  void emplace(const P1& p1, const P2& p2, const P3& p3) {
    EnsureDisengaged();
    new (value_memory_.void_data()) T(p1, p2, p3);
    engaged_ = true;
#if !defined(NDEBUG)
    value_ptr_ = static_cast<const T*>(value_memory_.void_data());
#endif
  }
  template <typename P1, typename P2, typename P3, typename P4>
  void emplace(const P1& p1, const P2& p2, const P3& p3, const P4& p4) {
    EnsureDisengaged();
    new (value_memory_.void_data()) T(p1, p2, p3, p4);
    engaged_ = true;
#if !defined(NDEBUG)
    value_ptr_ = static_cast<const T*>(value_memory_.void_data());
#endif
  }
  template <typename P1, typename P2, typename P3, typename P4, typename P5>
  void emplace(const P1& p1, const P2& p2, const P3& p3, const P4& p4,
      const P5& p5) {
    EnsureDisengaged();
    new (value_memory_.void_data()) T(p1, p2, p3, p4, p5);
    engaged_ = true;
#if !defined(NDEBUG)
    value_ptr_ = static_cast<const T*>(value_memory_.void_data());
#endif
  }
  template <typename P1, typename P2, typename P3, typename P4, typename P5,
      typename P6>
  void emplace(const P1& p1, const P2& p2, const P3& p3, const P4& p4,
      const P5& p5, const P6& p6) {
    EnsureDisengaged();
    new (value_memory_.void_data()) T(p1, p2, p3, p4, p5, p6);
    engaged_ = true;
#if !defined(NDEBUG)
    value_ptr_ = static_cast<const T*>(value_memory_.void_data());
#endif
  }
  template <typename P1, typename P2, typename P3, typename P4, typename P5,
      typename P6, typename P7>
  void emplace(const P1& p1, const P2& p2, const P3& p3, const P4& p4,
      const P5& p5, const P6& p6, const P7& p7) {
    EnsureDisengaged();
    new (value_memory_.void_data()) T(p1, p2, p3, p4, p5, p6, p7);
    engaged_ = true;
#if !defined(NDEBUG)
    value_ptr_ = static_cast<const T*>(value_memory_.void_data());
#endif
  }
// End emplace(...) definitions ////////////////////////////////////////////////
