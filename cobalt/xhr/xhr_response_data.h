/*
 * Copyright 2015 Google Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef XHR_XHR_RESPONSE_DATA_H_
#define XHR_XHR_RESPONSE_DATA_H_

#include "base/memory/scoped_ptr.h"

namespace cobalt {
namespace xhr {

// Simple wrapper for an array of data.
// Used by XMLHttpRequest to construct the response body.
class XhrResponseData {
 public:
  XhrResponseData();
  ~XhrResponseData();

  // Destroy the data_ and reset the size and capacity to 0.
  void Clear();
  // Allocate storage for |new_capacity_bytes| of data.
  void Reserve(size_t new_capacity_bytes);
  // Append |source_data|, |size_bytes| in length, to the data array.
  void Append(const uint8* source_data, size_t size_bytes);

  // Transfers ownership to the caller, and effectively Clear()s this object.
  scoped_array<uint8> Pass();

  const uint8* data() const { return data_.get(); }
  uint8* data() { return data_.get(); }

  size_t size() const { return size_; }
  size_t capacity() const { return capacity_; }

 private:
  scoped_array<uint8> data_;
  size_t size_;
  size_t capacity_;
};

}  // namespace xhr
}  // namespace cobalt

#endif  // XHR_XHR_RESPONSE_DATA_H_
