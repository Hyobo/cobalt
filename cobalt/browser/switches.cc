/*
 * Copyright 2014 Google Inc. All Rights Reserved.
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

#include "cobalt/browser/switches.h"

namespace cobalt {
namespace browser {
namespace switches {

#if defined(ENABLE_COMMAND_LINE_SWITCHES)
// Allow insecure HTTP network connections.
const char kAllowHttp[] = "allow_http";

// Switches different debug console modes: on | hud | off
const char kDebugConsoleMode[] = "debug_console";

// Disable the content security policy.
const char kDisableCsp[] = "disable_csp";

// Create WebDriver server.
const char kEnableWebDriver[] = "enable_webdriver";

// Additional base directory for accessing web files via file://.
const char kExtraWebFileDir[] = "web_file_path";

// Setting this switch causes all certificate errors to be ignored.
const char kIgnoreCertificateErrors[] = "ignore_certificate_errors";

// Setting this switch defines the startup URL that Cobalt will use.  If no
// value is set, a default URL will be used.
const char kInitialURL[] = "url";

// If this flag is set, input will be continuously generated randomly instead of
// taken from an external input device (like a controller).
const char kInputFuzzer[] = "input_fuzzer";

// Specifies a proxy to use for network connections.
const char kProxy[] = "proxy";

// Switches partial layout: on | off
const char kPartialLayout[] = "partial_layout";

// Creates a remote debugging server and listens on the specified port.
const char kRemoteDebuggingPort[] = "remote_debugging_port";

// If this flag is set, Cobalt will automatically shutdown after the specified
// number of seconds have passed.
const char kShutdownAfter[] = "shutdown_after";

// If this is set, then a trace (see base/debug/trace_eventh.h) is started on
// Cobalt startup.  A value must also be specified for this switch, which is
// the duration in seconds of how long the trace will be done for before ending
// and saving the results to disk.  Results will be saved to the file
// "timed_trace.json" in the log output directory.
const char kTimedTrace[] = "timed_trace";

// Port that the WebDriver server should be listening on.
const char kWebDriverPort[] = "webdriver_port";

#endif  // ENABLE_COMMAND_LINE_SWITCHES

}  // namespace switches
}  // namespace browser
}  // namespace cobalt
