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
namespace kosmic::theory {

template<typename FieldT, typename MetricT, typename ParametersT>
class TheoryDynamics {
  public:
    virtual ~TheoryDynamics() = default;

    // Given current field values, metric, and this theory's concrete
    // parameters, compute time derivatives (EOM). Hot path -- called every
    // integrator step, every lattice site.
    virtual void EquationsOfMotion(const FieldT& fields,
                                    const MetricT& metric,
                                    const ParametersT& params,
                                    FieldT& dFieldsDt) const = 0;

    // Energy density per site -- required by AMR refinement and by
    // augmentation's clustering step. Every theory has one.
    virtual LatticeScalarField EnergyDensity(const FieldT& fields,
                                              const MetricT& metric,
                                              const ParametersT& params) const = 0;

    // Theory-specific topological/conserved charge (e.g. winding number).
    // Not every theory has one, hence optional.
    virtual std::optional<LatticeScalarField> TopologicalCharge(
        const FieldT& fields, const ParametersT& params) const {
        return std::nullopt;
    }

    // Initial conditions -- theory-specific by nature (thermal spectrum,
    // seeded defects, vacuum, etc.), so part of the contract rather than
    // generic simulation-runner code.
    virtual void Initialize(FieldT& fields,const MetricT& metric, const ParametersT& params,
                             const InitParams& initParams) const = 0;
};

}  // namespace kosmic::theory
