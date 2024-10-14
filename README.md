# Marble Soccer Simulation

Marble Soccer Simulation is a C-based project, developed during a hackathon.
The simulation models the movement and interaction of marbles in a 2D space, designed specifically to train reinforcement learning agents to play marble soccer.

## Features

- **High-speed Simulation**: Run the simulation without rendering for faster performance, ideal for training agents.
- **Optional Rendering**: Use the `--render` flag to visualize the simulation.
- **Reinforcement Learning Integration**: Designed with agent training in mind, enabling the use of machine learning algorithms to optimize game strategy.

## Requirements

- **SDL Library**: Make sure to install the SDL2 library before building the project.
- **C Compiler**: Compatible with most modern C compilers.

## Build and Run Instructions

1. **Build the project**:

   ```bash
   make
   ```

2. **Run the simulation**:
   ```bash
    ./app --render
   ```
