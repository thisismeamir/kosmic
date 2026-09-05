# augment: lattice cropping/recombination pipeline. Consumes snapshots via
# storage/ only — never depends on core/ internals. Stays in-monorepo for
# now; split into its own repo once its API stabilizes.
add_subdirectory(cluster)
add_subdirectory(recombine)
add_subdirectory(provenance)
