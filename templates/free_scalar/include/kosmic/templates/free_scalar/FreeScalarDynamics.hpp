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
// Kosmic Templates Namespace:
// FreeScalar composes core/theory's ScalarField building block with no
// potential term -- the simplest possible complete theory, used to
// validate the full Field / TheoryInterface / Metric / Integrator pipeline
// end-to-end before trusting the same pattern for AbelianHiggs.
#include <cmath>
#include <optional>

#include "kosmic/field/Field.hpp"
#include "kosmic/theory/TheoryInterface.hpp"
#include "kosmic/theory/fields/Scalarfield.hpp"
#include "kosmic/theory/InitParams.hpp"
namespace kosmic::templates::free_scalar {

// No independent/derived parameters -- a free field has no coupling, no
// potential, nothing to scan over. Constants/IndependentParameters/
// DerivedParameters are all left as their empty defaults from
// TheoryParameters.
class FreeScalarParameters : public kosmic::theory::TheoryParameters {
  public:
    FreeScalarParameters()
        : TheoryParameters(kosmic::theory::Constants{},
                            kosmic::theory::IndependentParameters{}) {}

  protected:
    kosmic::theory::DerivedParameters computeDerived() const override {
        return kosmic::theory::DerivedParameters{};
    }
};

using kosmic::field::CpuLatticeScalarField;

template<typename FieldT, typename MetricT>
class FreeScalarDynamics {
  public:
    void EquationsOfMotion(const FieldT& fields, const MetricT& /*metric*/,
                            const FreeScalarParameters& /*params*/,
                            FieldT& force) const {
        force *= 0.0;
        // Free field: force is purely the Laplacian, no potential term.
        // force is not zeroed here -- caller owns that, matching
        // ScalarField::LaplacianContribution's accumulate-only contract.
        kosmic::theory::fields::ScalarField<FieldT>::LaplacianContribution(
            fields, force, /*component=*/0, dx_);
    }

    std::optional<FieldT> TopologicalCharge(const FieldT&,
                                             const FreeScalarParameters&) const {
        // A free real scalar has no topological charge.
        return std::nullopt;
    }

    void Initialize(FieldT& fields, const FreeScalarParameters&,
                   const MetricT&,
                   const kosmic::theory::InitParams& initParams) const {
      const unsigned int sizeX = fields.SizeX();
      const unsigned int sizeY = fields.SizeY();
      const unsigned int sizeZ = fields.SizeZ();

      // One full wavelength across the x-direction of the lattice.
      const double k = 2.0 * M_PI / static_cast<double>(sizeX);
      const double amplitude = 0.01;

      for (unsigned int x = 0; x < sizeX; ++x) {
          for (unsigned int y = 0; y < sizeY; ++y) {
              for (unsigned int z = 0; z < sizeZ; ++z) {
                  fields.At(x, y, z, 0) = amplitude * std::sin(k * x);
              }
          }
      }
  }

  private:
    double dx_ = 1.0;  // lattice spacing; TODO surface as a real config value
};

}  // namespace kosmic::templates::free_scalar
