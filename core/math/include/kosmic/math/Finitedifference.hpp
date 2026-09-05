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
// Kosmic Math Namespace:
// Discrete differential operators shared across theory building blocks.
// Kept theory-agnostic -- operates on any Field<N, LayoutPolicy> via a
// PeriodicAccessor, one component at a time.
#include "kosmic/field/Field.hpp"
#include "kosmic/field/PeriodicAccessor.hpp"

namespace kosmic::math {

// Standard second-order, 7-point (in 3D) central-difference Laplacian of
// one field component at site (x, y, z), with lattice spacing dx (assumed
// equal in all three directions for now).
template<typename FieldT>
double Laplacian(kosmic::field::PeriodicAccessor<FieldT>& accessor,
                  int x, int y, int z, unsigned int component, double dx) {
    double center = accessor.At(x, y, z, component);

    double sumNeighbors =
        accessor.At(x + 1, y, z, component) + accessor.At(x - 1, y, z, component) +
        accessor.At(x, y + 1, z, component) + accessor.At(x, y - 1, z, component) +
        accessor.At(x, y, z + 1, component) + accessor.At(x, y, z - 1, component);

    return (sumNeighbors - 6.0 * center) / (dx * dx);
}

}  // namespace kosmic::math
