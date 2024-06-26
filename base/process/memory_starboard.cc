// Copyright 2018 Google Inc. All Rights Reserved.
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

#include "base/process/memory.h"

#include <cstdlib>

#include "starboard/memory.h"

namespace base {

void EnableTerminationOnOutOfMemory() {
  // Nothing to be done here.
}

void EnableTerminationOnHeapCorruption() {
  // Nothing to be done here.
}

bool UncheckedMalloc(size_t size, void** result) {
  *result = malloc(size);
  return *result != nullptr;
}

void UncheckedFree(void* ptr) {
  free(ptr);
}

}  // namespace base
