/*
 * Copyright 2018 Google Inc. All Rights Reserved.
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

#ifndef STARBOARD_COMMON_THREAD_H_
#define STARBOARD_COMMON_THREAD_H_

#include <functional>
#include <string>

#include "starboard/common/scoped_ptr.h"
#include "starboard/configuration.h"
#include "starboard/thread.h"
#include "starboard/types.h"

namespace starboard {

class Semaphore;

class Thread {
 public:
  struct Options {
    int64_t stack_size = 0;  // Signal for default stack size.
    SbThreadPriority priority_ = kSbThreadNoPriority;
    bool joinable = true;    // False - detached (daemon) thread.
  };

  // Convenience function to create a Thread from the given
  // run function. The run function will be passed the join
  // semaphore, which will have Put() invoked once when join
  // is called.
  // Thread starts out in a stopped state.
  // Example:
  //  std::function<void(Semaphore*)> run_function = ...;
  //  scoped_ptr<Thread> thread = CreateNewThread("MyThread", run_function);
  //  thread->Start();
  //  ...
  //  thread->Join();
  static scoped_ptr<Thread> Create(
      const std::string& thread_name,
      std::function<void(Semaphore*)> run_function);

  explicit Thread(const std::string& name);
  virtual ~Thread();

  // Subclasses should override the Run method.
  // Example:
  //  void Run() {
  //    while (!WaitForJoin(kWaitTime)) {
  //      ... do work ...
  //    }
  //  }
  virtual void Run() = 0;

  // Called by the main thread, this will cause Run() to be invoked
  // on another thread.
  void Start(const Options& options = Options());
  void Join();
  bool join_called() const;

 protected:
  static void Sleep(SbTime microseconds);
  static void SleepMilliseconds(int value);

  // Waits at most |timeout| microseconds for Join() to be called. If
  // Join() was called then return |true|, else |false|.
  bool WaitForJoin(SbTime timeout);
  Semaphore* join_sema();

 private:
  static void* ThreadEntryPoint(void* context);

  struct Data;
  scoped_ptr<Data> d_;

  SB_DISALLOW_COPY_AND_ASSIGN(Thread);
};

}  // namespace starboard

#endif  // STARBOARD_COMMON_THREAD_H_
