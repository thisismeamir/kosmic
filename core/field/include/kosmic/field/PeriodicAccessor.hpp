/*
 * Copyright 2026 Independent Society of Knowledge (ISK)
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
// SPDX-License-Identifier: Apache-2.0
#pragma once
// Kosmic Field Namespace:
// PeriodicAccessor wraps a Field and handles periodic boundary wraparound,
// so Field itself stays boundary-agnostic. Other boundary types (fixed,
// open) become sibling accessors later without touching Field.

#include "Field.hpp"

namespace kosmic::field {

template<typename FieldT>
class PeriodicAccessor {
  public:
    explicit PeriodicAccessor(FieldT& field) : field_(field) {}

    decltype(auto) At(int x, int y, int z, unsigned int component) {
        return field_.At(Wrap(x, field_.SizeX()),
                         Wrap(y, field_.SizeY()),
                         Wrap(z, field_.SizeZ()),
                         component);
    }

    decltype(auto) At(int x, int y, int z, unsigned int component) const {
        return field_.At(Wrap(x, field_.SizeX()),
                         Wrap(y, field_.SizeY()),
                         Wrap(z, field_.SizeZ()),
                         component);
    }

  private:
    static unsigned int Wrap(int index, unsigned int size) {
        int wrapped = index % static_cast<int>(size);
        if (wrapped < 0) {
            wrapped += static_cast<int>(size);
        }
        return static_cast<unsigned int>(wrapped);
    }

    FieldT& field_;
};
}  // namespace kosmic::field
