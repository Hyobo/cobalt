// Copyright 2018 The Cobalt Authors. All Rights Reserved.
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

// clang-format off

// This file has been auto-generated by bindings/code_generator_cobalt.py. DO NOT MODIFY!
// Auto-generated from template: bindings/v8c/templates/callback-interface.cc.template


#include "cobalt/bindings/testing/v8c_single_operation_interface.h"
#include "cobalt/bindings/testing/arbitrary_interface.h"
#include "cobalt/bindings/testing/v8c_arbitrary_interface.h"

#include "v8c_gen_type_conversion.h"

#include "cobalt/script/logging_exception_state.h"
#include "cobalt/script/v8c/entry_scope.h"
#include "cobalt/script/v8c/helpers.h"
#include "cobalt/script/v8c/v8c_callback_interface.h"
#include "cobalt/script/v8c/v8c_global_environment.h"
#include "v8/include/v8.h"

namespace {
using cobalt::bindings::testing::SingleOperationInterface;
using cobalt::bindings::testing::V8cSingleOperationInterface;
using cobalt::bindings::testing::ArbitraryInterface;
using cobalt::bindings::testing::V8cArbitraryInterface;

using cobalt::script::LoggingExceptionState;
using cobalt::script::v8c::EntryScope;
using cobalt::script::v8c::FromJSValue;
using cobalt::script::v8c::GetCallableForCallbackInterface;
using cobalt::script::v8c::NewInternalString;
using cobalt::script::v8c::ToJSValue;
using cobalt::script::v8c::V8cGlobalEnvironment;
}  // namespace

namespace cobalt {
namespace bindings {
namespace testing {

base::optional<int32_t > V8cSingleOperationInterface::HandleCallback(
    const scoped_refptr<script::Wrappable>& callback_this,
    const scoped_refptr<ArbitraryInterface>& value,
    bool* had_exception) const {
  bool success = false;
  base::optional<int32_t > cobalt_return_value;

  DCHECK(isolate_);
  DCHECK(!this->IsEmpty());
  {
    EntryScope entry_scope(isolate_);
    v8::Local<v8::Context> context = isolate_->GetCurrentContext();
    v8::TryCatch try_catch(isolate_);

    v8::Local<v8::Value> implementing_value = this->NewLocal(isolate_);
    if (!implementing_value->IsObject()) {
      LOG(WARNING) << "Implementing object is NULL";
      goto done;
    }

    v8::Local<v8::Function> callable;
    if (!GetCallableForCallbackInterface(
             isolate_, implementing_value.As<v8::Object>(),
             NewInternalString(isolate_, "handleCallback"))
             .ToLocal(&callable)) {
      goto done;
    }

    v8::Local<v8::Value> this_value;
    ToJSValue(isolate_, callback_this, &this_value);

    const int kNumArguments = 1;
    v8::Local<v8::Value> argv[kNumArguments];
    ToJSValue(isolate_, value, &argv[0]);

    v8::Local<v8::Value> return_value;
    if (!callable->Call(context, this_value, kNumArguments, argv)
             .ToLocal(&return_value)) {
      goto done;
    }
    LoggingExceptionState exception_state;
    FromJSValue(isolate_, return_value, 0, &exception_state,
                &cobalt_return_value);
    success = !exception_state.is_exception_set();
  }

done:
  *had_exception = !success;
  return cobalt_return_value;

}

}  // namespace testing
}  // namespace bindings
}  // namespace cobalt

