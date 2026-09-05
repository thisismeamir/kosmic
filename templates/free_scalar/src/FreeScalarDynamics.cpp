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
#include <kosmic/templates/free_scalar/FreeScalarDynamics.hpp>

// FreeScalarDynamics itself is a template (per FieldT/MetricT), so it is
// fully defined in the header -- nothing to instantiate here yet.
// FreeScalarParameters is a concrete, non-template class, but every one of
// its methods is already defined inline in the header (constructor
// delegates to the base, computeDerived is a one-liner) -- there is
// currently nothing left that needs an out-of-line definition.
//
// This translation unit exists so KosmicTemplateFreeScalar has at least
// one .cpp to build against; it will pick up real content once
// FreeScalarDynamics::Initialize is implemented, or if
// FreeScalarParameters grows non-trivial methods later.
