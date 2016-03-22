/*
 * Copyright 2016 Google Inc. All Rights Reserved.
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

#include "cobalt/network/user_agent_string_factory.h"

#include "base/stringprintf.h"

namespace cobalt {
namespace network {

namespace {

class UserAgentStringFactoryStarboard : public UserAgentStringFactory {
 public:
  UserAgentStringFactoryStarboard();
};

UserAgentStringFactoryStarboard::UserAgentStringFactoryStarboard() {
  os_name_and_version_ = base::StringPrintf("Starboard %d", SB_API_VERSION);
}

}  // namespace

scoped_ptr<UserAgentStringFactory>
UserAgentStringFactory::ForCurrentPlatform() {
  return scoped_ptr<UserAgentStringFactory>(
      new UserAgentStringFactoryStarboard());
}

}  // namespace network
}  // namespace cobalt
