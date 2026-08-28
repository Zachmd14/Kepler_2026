# Kepler_2026

A C simulation of planetary orbital trajectories (Mercury, Venus, Earth, Mars) around the Sun, comparing three numerical integration methods:

- **Euler Simple**
- **Euler Asymmetric**
- **Runge-Kutta 2**

For each planet and method, the simulation computes trajectories and mechanical energy conservation, exporting results to JSON and CSV for analysis/visualization.

## Build

```bash
make release   # optimized build
make debug     # debug build
```

Produces an `executable` symlink in the project root.

## Run

```bash
./executable
```

You'll be prompted for the number of years to simulate. Output files are written to the working directory:

- `trajectoire*.json` — per-planet/method position & velocity trajectories
- `energies*.csv` — mechanical energy over time (used to assess integrator accuracy)

## Project structure

| File / Folder      | Description                                  |
|---------------------|-----------------------------------------------|
| `main.c`             | Entry point, orchestrates simulations & exports |
| `functions.c/.h`     | Core physics (integrators, orbital mechanics) |
| `vecteurs.c/.h`      | 3D vector math                                |
| `constants.h`        | Physical constants (masses, orbital elements) |
| `site/`, `site_energies/` | Visualization front-ends for the exported data |
| `Makefile`           | Build configuration                           |

## Requirements

- GCC (or compatible C99 compiler)
- `make`

## License

None

