# Monte Carlo Simulation of Photon Transport

This project uses Monte Carlo methods to simulate random processes, specifically:

- Sampling exponential distributions via rejection and cumulative methods
- Modeling photon scattering and absorption in a 3D medium with directional binning

## Contents

### 1. `generating_samples.c`
Simulates two methods of sampling from an exponential distribution:
- **Rejection sampling** using a basic `exp(-x)` envelope
- **Cumulative sampling** using inverse transform sampling

Outputs are binned to compare the generated distributions.

### 2. `photon_sim.c`
Simulates photon propagation through a medium:
- Photons start at the origin and are randomly scattered or absorbed
- Photons are tracked in 3D using spherical coordinates (`r`, `θ`, `φ`)
- Simulation continues until photons exit a plane at `z = z_max` or are absorbed
- Exit directions are binned by angle

