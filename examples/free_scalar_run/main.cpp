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
//
// First end-to-end run of the Kosmic pipeline: a free real scalar field on
// a periodic lattice, evolved with the staggered leapfrog integrator in
// flat space. No potential, no gauge sector -- this exists purely to
// validate Field / TheoryInterface / Metric / Integrator work together
// correctly before trusting the same pattern for AbelianHiggs.
//
// fieldsDot is owned here (per our "caller owns it" decision for
// LeapfrogIntegrator) and left at its default zero-initialized state,
// which is the physically correct initial velocity for the standing wave
// FreeScalarDynamics::Initialize seeds into `fields`.
#include <cmath>
#include <iostream>

#include "kosmic/geometry/Metric.hpp"
#include "kosmic/integrator/LeapFrogIntegrator.hpp"
#include "kosmic/templates/free_scalar/FreeScalarDynamics.hpp"
#include "kosmic/theory/TheoryInterface.hpp"

using kosmic::field::CpuLatticeScalarField;
using kosmic::geometry::FlatMetric;
using kosmic::templates::free_scalar::FreeScalarDynamics;
using kosmic::templates::free_scalar::FreeScalarParameters;

namespace {

// Total energy = kinetic + gradient, summed over the lattice. For a free
// scalar this should stay constant (up to leapfrog's own discretization
// error) over the run -- our first real correctness check.
double TotalEnergy(const CpuLatticeScalarField &fields,
                   const CpuLatticeScalarField &fieldsDot, double dx) {
  double energy = 0.0;
  const unsigned int sizeX = fields.SizeX();
  const unsigned int sizeY = fields.SizeY();
  const unsigned int sizeZ = fields.SizeZ();

  for (unsigned int x = 0; x < sizeX; ++x) {
    for (unsigned int y = 0; y < sizeY; ++y) {
      for (unsigned int z = 0; z < sizeZ; ++z) {
        double velocity = fieldsDot.At(x, y, z, 0);
        double kinetic = 0.5 * velocity * velocity;

        // Forward-difference gradient in x only, matching the
        // plane wave's only direction of variation.
        unsigned int xNext = (x + 1) % sizeX;
        double dPhiDx =
            (fields.At(xNext, y, z, 0) - fields.At(x, y, z, 0)) / dx;
        double gradient = 0.5 * dPhiDx * dPhiDx;

        energy += kinetic + gradient;
      }
    }
  }
  return energy;
}

} // namespace

int main() {
  const unsigned int latticeSize = 32;
  const double dx = 1.0;
  const double dt = 0.1;
  const unsigned int numSteps = 5000;
  const unsigned int reportEvery = 10;

  CpuLatticeScalarField fields(latticeSize, latticeSize, latticeSize);
  CpuLatticeScalarField fieldsDot(latticeSize, latticeSize, latticeSize);

  FreeScalarParameters params;
  FreeScalarDynamics<CpuLatticeScalarField, FlatMetric> dynamics;
  FlatMetric metric;

  kosmic::theory::InitParams initParams;
  dynamics.Initialize(fields, params, metric, initParams);
  // fieldsDot left at its zero-initialized default -- correct initial
  // velocity for a standing wave.

  kosmic::integrator::LeapfrogIntegrator<
      CpuLatticeScalarField, FlatMetric, FreeScalarParameters,
      FreeScalarDynamics<CpuLatticeScalarField, FlatMetric>>
      integrator(dynamics, params, metric);

  double time = 0.0;
  for (unsigned int step = 0; step < numSteps; ++step) {
    integrator.Step(fields, fieldsDot, time, dt);
    time += dt;

    if (step % reportEvery == 0) {
      std::cout << "step " << step << "  t = " << time
                << "  energy = " << TotalEnergy(fields, fieldsDot, dx) << "\n";
    }
  }

  return 0;
}
