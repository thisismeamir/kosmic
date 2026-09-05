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
// Kosmic Field Namespace:
// Field<N> is the lattice storage abstraction for an N-component field.
// Memory layout is selected at compile time via LayoutPolicy so CPU (AoS)
// and CUDA (SoA) backends compile as separate binaries with no runtime
// branching on layout. Field itself is boundary-agnostic -- see
// PeriodicAccessor for periodic boundary handling.
//
// Site indexing convention: row-major, z fastest-varying.
//   site = x * sizeY * sizeZ + y * sizeZ + z
//
// Layout convention:
//   AoS: storage_[site * N + component]              (component-major per site)
//   SoA: storage_[component * numSites + site]        (one block per component)
#include <cassert>
#include <cstddef>
#include <vector>

namespace kosmic::field {

struct AosLayout {};
struct SoaLayout {};

// FieldStorage encapsulates the layout-specific index math. Field<N,
// LayoutPolicy> delegates to the matching specialization -- this is the
// only place AoS vs. SoA index arithmetic lives. Both specializations
// additionally expose Data()/Size() so Field's operators (+=, *=) can walk
// the underlying buffer directly, without caring which layout it is --
// elementwise arithmetic gives the same result regardless of ordering.
template<unsigned int N, typename LayoutPolicy>
class FieldStorage;

template<unsigned int N>
class FieldStorage<N, AosLayout> {
  public:
    explicit FieldStorage(std::size_t numSites) : data_(numSites * N, 0.0) {}

    double& At(std::size_t site, unsigned int component) {
        return data_[site * N + component];
    }
    const double& At(std::size_t site, unsigned int component) const {
        return data_[site * N + component];
    }

    double* Data() { return data_.data(); }
    const double* Data() const { return data_.data(); }
    std::size_t Size() const { return data_.size(); }

  private:
    std::vector<double> data_;
};

template<unsigned int N>
class FieldStorage<N, SoaLayout> {
  public:
    explicit FieldStorage(std::size_t numSites)
        : numSites_(numSites), data_(numSites * N, 0.0) {}

    double& At(std::size_t site, unsigned int component) {
        return data_[component * numSites_ + site];
    }
    const double& At(std::size_t site, unsigned int component) const {
        return data_[component * numSites_ + site];
    }

    double* Data() { return data_.data(); }
    const double* Data() const { return data_.data(); }
    std::size_t Size() const { return data_.size(); }

  private:
    std::size_t numSites_;
    std::vector<double> data_;
};

template<unsigned int N, typename LayoutPolicy>
class Field {
  public:
    Field(unsigned int sizeX, unsigned int sizeY, unsigned int sizeZ)
        : sizeX_(sizeX),
          sizeY_(sizeY),
          sizeZ_(sizeZ),
          storage_(static_cast<std::size_t>(sizeX) * sizeY * sizeZ) {}

    double& At(unsigned int x, unsigned int y, unsigned int z, unsigned int component) {
        return storage_.At(SiteIndex(x, y, z), component);
    }
    const double& At(unsigned int x, unsigned int y, unsigned int z, unsigned int component) const {
        return storage_.At(SiteIndex(x, y, z), component);
    }

    unsigned int SizeX() const { return sizeX_; }
    unsigned int SizeY() const { return sizeY_; }
    unsigned int SizeZ() const { return sizeZ_; }
    static constexpr unsigned int NumComponents() { return N; }

    // self += other * scalar, in one pass -- avoids the temporary Field
    // that `other * scalar` followed by `+=` would otherwise allocate.
    // This is the workhorse for leapfrog's kick/drift steps.
    Field& AddScaled(const Field& other, double scalar) {
      assert(storage_.Size() == other.storage_.Size());
      double* self = storage_.Data();
      const double* rightHandSide = other.storage_.Data();
      for(std::size_t i = 0; i < storage_.Size(); ++i) {
        self[i] += rightHandSide[i] * scalar;
      }
      return *this;
    }


    // Elementwise in-place addition. Sizes must match (checked via assert,
    // not an exception -- these run in the hot loop and are expected to
    // only ever be called with matching lattices).
    Field& operator+=(const Field& other) {
        assert(storage_.Size() == other.storage_.Size());
        double* self = storage_.Data();
        const double* rhs = other.storage_.Data();
        for (std::size_t i = 0; i < storage_.Size(); ++i) {
            self[i] += rhs[i];
        }
        return *this;
    }

    // Elementwise in-place scalar multiplication.
    Field& operator*=(double scalar) {
        double* self = storage_.Data();
        for (std::size_t i = 0; i < storage_.Size(); ++i) {
            self[i] *= scalar;
        }
        return *this;
    }

  private:
    std::size_t SiteIndex(unsigned int x, unsigned int y, unsigned int z) const {
        return (static_cast<std::size_t>(x) * sizeY_ + y) * sizeZ_ + z;
    }

    unsigned int sizeX_;
    unsigned int sizeY_;
    unsigned int sizeZ_;
    FieldStorage<N, LayoutPolicy> storage_;
};

using CpuLatticeScalarField = Field<1, AosLayout>;
using CudaLatticeScalarField = Field<1, SoaLayout>;

}  // namespace kosmic::field
