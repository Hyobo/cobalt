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

#ifndef INPUT_KEYPRESS_GENERATOR_FILTER_H_
#define INPUT_KEYPRESS_GENERATOR_FILTER_H_

#include "cobalt/input/key_event_handler.h"

namespace cobalt {
namespace input {

// Generates an additional keypress event for keydown events that correspond
// to a printable character or BS/Enter.
class KeypressGeneratorFilter : public KeyEventHandler {
 public:
  explicit KeypressGeneratorFilter(const KeyboardEventCallback& callback);

  explicit KeypressGeneratorFilter(KeyEventHandler* filter);

  // Conditionally generates an additional keypress event.
  // Passes on the new and original events for further processing/handling.
  void HandleKeyboardEvent(
      const scoped_refptr<dom::KeyboardEvent>& event) OVERRIDE;

 protected:
  // Generates a keypress event, if:
  // 1. The original event is a keydown.
  // 2. The keycode corresponds to a printable character, or BS/Enter.
  bool ConditionallyGenerateKeypressEvent(
      const scoped_refptr<dom::KeyboardEvent>& orig_event);

  // Returns the character code corresponding to a keyboard event, or 0.
  // The character code is calculated using the keycode and modifier keys.
  // Returns 0 if the keycode doesn't correspond to a printable character.
  static int KeyboardEventToCharCode(
      const scoped_refptr<dom::KeyboardEvent>& keyboard_event);

  // Returns the character code corresponding to a Windows Virtual Key Code
  // with no shift modifier.
  static int KeyCodeToCharCodeNoShift(int key_code);

  // Returns the character code corresponding to a Windows Virtual Key Code
  // with a shift modifier.
  static int KeyCodeToCharCodeWithShift(int key_code);
};

}  // namespace input
}  // namespace cobalt

#endif  // INPUT_KEYPRESS_GENERATOR_FILTER_H_
