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
// Kosmic Theory Namespace:
// ScalarField is a generic real-scalar building block, reusable by any
// composed theory in templates/ that includes a scalar sector (FreeScalar,
// AbelianHiggs's radial mode, etc.). It knows only how to compute the
// kinetic (Laplacian) contribution to a scalar component's EOM -- it
// carries no potential term, since a potential is theory-specific and
// belongs in templates/, composed on top of this.
//
// Not itself a full TheoryDynamics implementation -- composed theories in
// templates/ call LaplacianContribution() from inside their own
// EquationsOfMotion, alongside whatever potential-derivative term they add.

#include "kosmic/field/Field.hpp"
#include "kosmic/field/PeriodicAccessor.hpp"
#include "kosmic/math/Finitedifference.hpp"

namespace kosmic::theory::fields {

template<typename FieldT>
class ScalarField {
  public:
    // Writes the Laplacian of `component` at every lattice site of `fields`
    // into the corresponding site/component of `force`. Does not clear
    // `force` first -- composed theories are expected to accumulate (add
    // the potential term on top), so callers that want a fresh value
    // should zero `force` themselves before calling.
    static void LaplacianContribution(const FieldT& fields, FieldT& force,
                                       unsigned int component, double dx) {
        kosmic::field::PeriodicAccessor<const FieldT> accessor(fields);

        for (unsigned int x = 0; x < fields.SizeX(); ++x) {
            for (unsigned int y = 0; y < fields.SizeY(); ++y) {
                for (unsigned int z = 0; z < fields.SizeZ(); ++z) {
                    force.At(x, y, z, component) +=
                        kosmic::math::Laplacian(accessor, static_cast<int>(x),
                                                 static_cast<int>(y),
                                                 static_cast<int>(z),
                                                 component, dx);
                }
            }
        }
    }
};

}  // namespace kosmic::theory
