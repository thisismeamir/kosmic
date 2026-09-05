#pragma once
// core/theory/interface: the theory plugin contract. Every field theory
// (Abelian Higgs and any future theory) implements this so the integrator,
// AMR, and augmentation clustering can operate without theory-specific
// knowledge.
//
// TODO: field_layout(), equations_of_motion(), energy_density(),
// optional topological_charge(), initialize().
namespace kosmic::theory {}
