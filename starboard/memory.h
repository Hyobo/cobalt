// Copyright 2015 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Memory allocation, alignment, copying, and comparing.

#ifndef STARBOARD_MEMORY_H_
#define STARBOARD_MEMORY_H_

#include "starboard/export.h"
#include "starboard/types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SB_MEMORY_MAP_FAILED ((void*)-1)  // NOLINT(readability/casting)

// Checks whether |memory| is aligned to |alignment| bytes.
static SB_C_FORCE_INLINE bool SbMemoryIsAligned(const void* memory,
                                                size_t alignment) {
  return ((uintptr_t)memory) % alignment == 0;
}

// Allocates a chunk of memory of at least |size| bytes, returning it. If unable
// to allocate the memory, it returns NULL. If |size| is 0, it may return NULL
// or it may return a unique pointer value that can be passed to
// SbMemoryFree. Meant to be a drop-in replacement for malloc.
SB_EXPORT void* SbMemoryAllocate(size_t size);

// Attempts to resize |memory| to be at least |size| bytes, without touching the
// contents. If it cannot perform the fast resize, it will allocate a new chunk
// of memory, copy the contents over, and free the previous chunk, returning a
// pointer to the new chunk. If it cannot perform the slow resize, it will
// return NULL, leaving the given memory chunk unchanged. |memory| may be NULL,
// in which case it behaves exactly like SbMemoryAllocate.  If |size| is 0, it
// may return NULL or it may return a unique pointer value that can be passed to
// SbMemoryFree. Meant to be a drop-in replacement for realloc.
SB_EXPORT void* SbMemoryReallocate(void* memory, size_t size);

// Frees a previously allocated chunk of memory. If |memory| is NULL, then it
// does nothing.  Meant to be a drop-in replacement for free.
SB_EXPORT void SbMemoryFree(void* memory);

// Allocates a chunk of memory of at least |size| bytes, aligned to |alignment|,
// returning it. |alignment| must be a power of two, otherwise behavior is
// undefined. If unable to allocate the memory, it returns NULL. If |size| is 0,
// it may return NULL or it may return a unique aligned pointer value that can
// be passed to SbMemoryFreeAligned. Meant to be a drop-in replacement for
// memalign.
SB_EXPORT void* SbMemoryAllocateAligned(size_t alignment, size_t size);

// Frees a previously allocated chunk of aligned memory. If |memory| is NULL,
// then it does nothing.  Meant to be a drop-in replacement for _aligned_free.
SB_EXPORT void SbMemoryFreeAligned(void* memory);

#if SB_HAS(MMAP)
// Allocates |size_bytes| worth of physical memory pages and maps them into an
// available virtual region. On some platforms, |name| appears in the debugger
// and can be up to 32 bytes. Returns SB_MEMORY_MAP_FAILED on failure, as NULL
// is a valid return value.
SB_EXPORT void* SbMemoryMap(int64_t size_bytes, const char* name);

// Unmap |size_bytes| of physical pages starting from |virtual_address|,
// returning true on success. After this, [virtual_address, virtual_address +
// size_bytes) will not be read/writable. SbMemoryUnmap() can unmap multiple
// contiguous regions that were mapped with separate calls to
// SbMemoryMap(). E.g. if one call to SbMemoryMap(0x1000) returns (void*)0xA000
// and another call to SbMemoryMap(0x1000) returns (void*)0xB000,
// SbMemoryUnmap(0xA000, 0x2000) should free both.
SB_EXPORT bool SbMemoryUnmap(void* virtual_address, int64_t size_bytes);
#endif  // SB_HAS(MMAP)

// Gets the stack bounds for the current thread, placing the highest addressable
// byte + 1 in |out_high|, and the lowest addressable byte in |out_low|.
SB_EXPORT void SbMemoryGetStackBounds(void** out_high, void** out_low);

// Copies |count| sequential bytes from |source| to |destination|, without
// support for the |source| and |destination| regions overlapping.  Behavior is
// undefined if |destination| or |source| are NULL. Does nothing if |count| is
// 0. Returns |destination|, for some reason. Meant to be a drop-in replacement
// for memcpy.
SB_EXPORT void* SbMemoryCopy(void* destination,
                             const void* source,
                             size_t count);

// Copies |count| sequential bytes from |source| to |destination|, with support
// for the |source| and |destination| regions overlapping.  Behavior is
// undefined if |destination| or |source| are NULL. Does nothing if |count| is
// 0. Returns |destination|, for some reason. Meant to be a drop-in replacement
// for memmove.
SB_EXPORT void* SbMemoryMove(void* destination,
                             const void* source,
                             size_t count);

// Fills |count| sequential bytes starting at |destination|, with the unsigned
// char coercion of |byte_value|. Behavior is undefined if |destination| is
// NULL. Returns |destination|, for some reason. Does nothing if |count| is 0.
// Meant to be a drop-in replacement for memset.
SB_EXPORT void* SbMemorySet(void* destination, int byte_value, size_t count);

// Compares the contents of the first |count| bytes of |buffer1| and |buffer2|.
// returns -1 if |buffer1| is "less-than" |buffer2|, 0 if they are equal, or 1
// if |buffer1| is "greater-than" |buffer2|.  Meant to be a drop-in replacement
// for memcmp.
SB_EXPORT int SbMemoryCompare(const void* buffer1,
                              const void* buffer2,
                              size_t count);

// Finds the lower 8-bits of |value| in the first |count| bytes of |buffer|,
// returning a pointer to the first found occurrence, or NULL if not
// found. Meant to be a drop-in replacement for memchr.
SB_EXPORT const void* SbMemoryFindByte(const void* buffer,
                                       int value,
                                       size_t count);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // STARBOARD_MEMORY_H_
