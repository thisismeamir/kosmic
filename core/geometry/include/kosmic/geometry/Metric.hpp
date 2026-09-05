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
#include <cmath>
namespace kosmic::geometry {
class FlatMetric {
  public:
    double ScaleFactor(double time) const { return 1.0; }
    double ScaleFactorDot(double time) const { return 0.0; }
};
class AnalyticFlrwMetric {
  public:
    AnalyticFlrwMetric(double a0, double t0, double p) : a0_(a0), t0_(t0), p_(p) {}
    double ScaleFactor(double time) const {
        return a0_ * std::pow(time / t0_, p_);
    }
    double ScaleFactorDot(double time) const {
        return a0_ * p_ / t0_ * std::pow(time / t0_, p_ - 1.0);
    }
  private:
    double a0_;
    double t0_;
    double p_;
};
} // namespace kosmic::geometry
