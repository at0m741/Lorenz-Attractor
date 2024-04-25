# Lorenz Attractor Visualization

This program visualizes the Lorenz Attractor using the Runge-Kutta 4th order method and SDL2 library for rendering.

## Introduction

The Lorenz Attractor is a set of chaotic solutions to a system of three ordinary differential equations. It is a classic example of a chaotic system, and its dynamic behavior is widely studied in various fields including mathematics, physics, and engineering.

## Dependencies

- SDL2 Library

## Installation

Make sure you have SDL2 installed on your system. You can install it using your package manager or download it from the SDL website: https://www.libsdl.org/download-2.0.php

Compile the program using any C compiler. For example, if you have `gcc` installed, you can compile the program by running:

```bash
gcc -o lorenz_attractor lorenz_attractor.c -lm -lSDL2
