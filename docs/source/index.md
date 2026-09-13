# Kosmic Docs

Kosmic
======

A generic lattice field theory simulator for cosmological field dynamics.

Kosmic provides a modular numerical framework for evolving field theories
on discrete spatial lattices, with particular emphasis on Abelian Higgs
cosmic string networks.

[Get Started] [Architecture] [Physics] [C++ API]

Why Kosmic?
-----------

    Field Theory
         │
         ▼
    Discretization
         │
         ▼
    Lattice State
         │
         ▼
    Time Integrator
         │
         ▼
    Execution Backend
         │
         ▼
    Observables / Snapshots

Core capabilities
-----------------

* Generic lattice fields
* Pluggable field theories
* Metric-aware evolution
* CPU reference backend
* CUDA backend
* Adaptive mesh refinement
* HDF5 simulation data
* Experiment provenance

Scientific scope
----------------

Kosmic is currently developed around Abelian Higgs cosmic string
simulations for gravitational-wave research.

Read more → Physics
