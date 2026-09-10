# Kosmic

Kosmic is a from-scratch lattice field theory simulation framework, built to
efficiently simulate Abelian Higgs cosmic string networks while staying
general enough to support other lattice field theories and metrics.

It is the simulation engine underlying the "Echoes of Symmetry Breaking"
thesis project, which uses simulation-based inference (SBI) with Abelian
Higgs lattice simulations to constrain cosmic string parameters from NANOGrav
PTA data. SBI itself is out of scope for this repository for now — Kosmic
is focused on producing a correct, efficient, and well-instrumented
simulation pipeline first.

## Goals

- **Generality**: the core should express "a field theory on a lattice with
  a given metric," not "Abelian Higgs." Abelian Higgs is the first and
  primary theory plugin, not a hardcoded assumption.
- **Modularity**: simulation core, GPU backend, adaptive mesh refinement,
  and data augmentation are independent modules with narrow, stable
  interfaces between them, so each can be developed and iterated on without
  the others changing.
- **Efficiency**: GPU-accelerated field evolution and adaptive mesh
  refinement are first-class citizens, not afterthoughts bolted onto a CPU
  reference implementation.
- **Novel augmentation**: alongside the simulation engine, Kosmic includes an
  augmentation pipeline that clusters simulated lattices into regions and
  recombines them across simulations to synthesize additional training
  configurations for downstream inference work — an approach not currently
  found elsewhere in the lattice field theory / SBI literature.

## Project layout

```
core/           C++ simulation kernel
  field/        Field<N> lattice storage abstraction
  geometry/     Metric abstraction (flat space, FLRW, ...)
  math/         Shared numerics (stencils, linear algebra) — prefers
                established libraries (BLAS, GSL, FFTW) over custom code
                wherever a solid one exists
  theory/       Pluggable theory definitions
    interface/  The theory plugin contract (EOM, energy density, ...)
    abelian_higgs/  Abelian Higgs implementation against that contract
  integrator/   Time evolution (staggered leapfrog)
  backend/      Execution backends
    cpu/        Reference implementation, correctness baseline
    cuda/       GPU-accelerated backend
  amr/          Adaptive mesh refinement
  api/          Stable, versioned public C++ API surface

augment/        Lattice clustering + recombination augmentation pipeline
  cluster/      Region clustering over lattice snapshots (e.g. Voronoi)
  recombine/    Cross-simulation region recombination, gap handling
  provenance/   Lineage metadata for synthetic lattices

storage/        Snapshot schema and dataset management
  schema/       HDF5 schema definitions
  manager/      Read/write and dataset versioning hooks

tracking/       Self-hosted experiment tracking configuration (MLflow)
orchestration/  Kotlin orchestration layer (not yet started)
sbi/            Mojo-based SBI layer (not yet started, out of scope for now)

tests/
  unit/         Unit tests
  regression/   Conserved-quantity regression tests (energy, winding number)

infra/
  docker/       Per-module container images (CUDA-pinned for the GPU backend)
  ci/           CI configuration
```

## Status

Early development. The current focus is the `core/theory/interface`
contract and the CPU reference backend; CUDA, AMR, and `augment/` build on
top of that once it is stable.

## Build

See `CMakeLists.txt` at the repo root. C++ core only for now — Kotlin
orchestration and Mojo SBI layers are deferred and not yet part of the
build.

## License

Apache-v2.0.
