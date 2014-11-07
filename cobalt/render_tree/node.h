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

#ifndef RENDER_TREE_NODE_H_
#define RENDER_TREE_NODE_H_

#include "base/memory/ref_counted.h"

namespace cobalt {
namespace render_tree {

class NodeVisitor;

// A base class of all objects that form a render tree.
class Node : public base::RefCountedThreadSafe<Node> {
 public:
  // A type-safe branching.
  virtual void Accept(NodeVisitor* visitor) = 0;

 protected:
  virtual ~Node() {}
  friend class base::RefCountedThreadSafe<Node>;
};

}  // namespace render_tree
}  // namespace cobalt

#endif  // RENDER_TREE_NODE_H_
