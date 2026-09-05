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
// Kosmic Integrator Namespace:
// LeapfrogIntegrator advances a field and its time-derivative field by one
// timestep using the staggered (kick-drift-kick) leapfrog scheme. It is
// templated on FieldT/MetricT/ParametersT/DynamicsT so the whole step is
// resolved at compile time -- no virtual dispatch in the hot loop, matching
// TheoryDynamics and Metric.
//
// LeapfrogIntegrator is stateless between calls: it does not own fields or
// fieldsDot -- the caller (simulation runner) owns both and passes them
// into Step() each time. This mirrors who owns `fields` in the first
// place, and keeps one LeapfrogIntegrator instance reusable across an
// entire run without per-step allocation.
//
// EquationsOfMotion is expected to compute the *second* time derivative of
// the fields (the force/acceleration acting on fieldsDot), not the first --
// fieldsDot itself only ever changes via the kick steps below.
#include "kosmic/theory/TheoryInterface.hpp"

namespace kosmic::integrator {

template<typename FieldT, typename MetricT, typename ParametersT, typename DynamicsT>
class LeapfrogIntegrator {
  public:
    LeapfrogIntegrator(const DynamicsT& dynamics, const ParametersT& params,
                        const MetricT& metric)
        : dynamics_(dynamics), params_(params), metric_(metric) {}

    // Advances fields and fieldsDot by dt, in place. `time` is the
    // simulation time at the start of the step (used for metric
    // evaluation inside EquationsOfMotion, if the theory needs it).
    void Step(FieldT& fields, FieldT& fieldsDot, double time, double dt) const {
        FieldT force(fields.SizeX(), fields.SizeY(), fields.SizeZ());

        // Kick (half-step): update fieldsDot using the force at the
        // current field configuration.
        dynamics_.EquationsOfMotion(fields, metric_, params_, force);
        fieldsDot.AddScaled(force, 0.5 * dt);

        // Drift (full-step): update fields using the half-kicked
        // fieldsDot.
        fields.AddScaled(fieldsDot, dt);

        // Kick (half-step): recompute the force at the new field
        // configuration and finish updating fieldsDot.
        dynamics_.EquationsOfMotion(fields, metric_, params_, force);
        fieldsDot.AddScaled(force, 0.5 * dt);
    }

  private:
    const DynamicsT& dynamics_;
    const ParametersT& params_;
    const MetricT& metric_;
};

}  // namespace kosmic::integrator
