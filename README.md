# Lorenz Attractor Visualization

This program visualizes the Lorenz Attractor using the Runge-Kutta 4th order method and SDL2 library for rendering.

## Introduction

The Lorenz Attractor is a set of chaotic solutions to a system of three ordinary differential equations. It was first studied by Edward Lorenz in 1963 while he was investigating atmospheric convection. The equations describe the dynamics of a simple model for atmospheric convection and exhibit chaotic behavior for certain parameter values.

## Mathematics

The Lorenz Attractor is governed by the following system of differential equations:
```math
\frac{dx}{dt} = \sigma(y - x)
```
```math
\frac{dy}{dt} = x(\rho - z) - y
```
```math
\frac{dz}{dt} = xy - \beta z
```

Where:
- $\(x\)$, $\(y\)$, and $\(z\)$ are the state variables representing the position of the system in three-dimensional space.
- $\(\sigma\)$, $\(\rho\)$, and $\(\beta\)$ are parameters of the system, controlling the behavior of the attractor.


## Dependencies

- SDL2 Library

## Installation

Make sure you have SDL2 installed on your system. You can install it using your package manager or download it from the SDL website: https://www.libsdl.org/download-2.0.php

Compile the program using any C compiler. For example, if you have `gcc` installed, you can compile the program by running:

```bash
gcc -o lorenz_attractor Lorenz.c -lm -lSDL2 -O3 -fopenmp -mvx2
