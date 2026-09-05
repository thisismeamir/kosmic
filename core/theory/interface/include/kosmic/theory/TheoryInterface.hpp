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
// Defines the contract of a theory, a field object that is going
// to evolve in a geometry is defined using this contract so that
// generality and extinsibility is preserved.
#include <memory>
#include <utility>

namespace kosmic::theory {


// Constants struct -- Fixed theory-defining, same across all runs of a theory.
struct Constants {};
 
// IndependentParameters struct -- the free parameters SBI will target
struct IndependentParameters {};
 
// DerivedParameters -- pure function of Independent + Constants, cached
struct DerivedParameters {};
 
// Data structure of all the theories parameters.
//
// Never construct a derived class of TheoryParameters directly -- the
// constructor is protected specifically to force construction through
// Create(), which is the only path that correctly populates derived_ via
// computeDerived() after the derived object fully exists. Calling a pure
// virtual from this class's own constructor would be undefined behavior,
// which is why derived_ is computed afterward, not inline in the
// constructor.
class TheoryParameters {
  public:
    // Theory-specific construction entry point. Usage:
    //   auto params = TheoryParameters::Create<AbelianHiggsParameters>(
    //       constants, independentParams);
    template<typename Derived, typename... Args>
    static std::unique_ptr<Derived> Create(Args&&... args) {
        auto obj = std::make_unique<Derived>(std::forward<Args>(args)...);
        obj->derived_ = obj->computeDerived();
        return obj;
    }
 
    virtual ~TheoryParameters() = default;
 
    const Constants& constants() const;
    const IndependentParameters& independent() const;
    // Valid only after construction via Create(); computed once and cached.
    const DerivedParameters& derived() const;
 
  protected:
    TheoryParameters(Constants constants, IndependentParameters iParams);
 
    // Theory-specific. Called exactly once, by Create(), after the derived
    // object is fully constructed.
    virtual DerivedParameters computeDerived() const = 0;
 
  private:
    Constants constants_;
    IndependentParameters independent_;
    DerivedParameters derived_;
};

}
