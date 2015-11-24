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

#include "cobalt/h5vcc/h5vcc_account_info.h"

#include "cobalt/account/account_manager.h"

namespace cobalt {
namespace h5vcc {

H5vccAccountInfo::H5vccAccountInfo(account::AccountManager* account_manager)
    : account_manager_(account_manager) {}

std::string H5vccAccountInfo::avatar_url() const {
  if (account_manager_) {
    DLOG(INFO) << "Got avatar URL: " << account_manager_->GetAvatarURL();
    return account_manager_->GetAvatarURL();
  }

  DLOG(WARNING) << "Account manager is NULL";
  return "";
}

std::string H5vccAccountInfo::username() const {
  NOTIMPLEMENTED();
  return "";
}

std::string H5vccAccountInfo::user_id() const {
  NOTIMPLEMENTED();
  return "";
}

}  // namespace h5vcc
}  // namespace cobalt
