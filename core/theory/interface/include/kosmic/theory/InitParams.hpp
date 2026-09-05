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

enum InitMode {
  Vacuum, Thermal, SeededDefects
};

struct InitParams {
  InitMode mode = InitMode::Vacuum;
  unsigned long seed = 0;
  // For Thermal mode
  double temperature = 0.0;
  // For SeededDefects mode
  unsigned int defecCount = 0;
};

}
