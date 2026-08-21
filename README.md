# C Project: Grid Robot Planning and Execution

## Description
This project simulates the planning and execution of a robot navigating a grid to collect packages, avoiding obstacles, and returning to base. The robot uses shortest-path algorithms (Dijkstra) to calculate efficient routes.

## Project Structure

- `src/` — Main source code
  - `main.c` — Main function and program workflow
  - `robot.c` — Robot logic (creation, planning, execution)
  - `grid.c` — Data structures and functions for grid manipulation
  - `map.c` — Random map generation
  - `pathfinder.c` — Dijkstra's algorithm for pathfinding
  - `structures.c` — Auxiliary data structures (min-heap, node)
  - `utils.c` — Utilities (delay, clear screen)
- `include/` — Header files for functions and structures
- `makefile` — Automated compilation

## How to Compile

1. Ensure you have GCC installed.
2. In your terminal, navigate to the project directory.
3. Run:

```sh
make
```

The executable will be generated in the root directory.

## How to Run

After compiling, run:

```sh
./robot_project
```

The program will:
- Generate a random grid with obstacles and packages
- Calculate the optimal route for the robot to collect all packages
- Simulate the robot's movement across the grid

## Key Features

- Random map generation with obstacles and packages
- Route planning using Dijkstra's algorithm
- Animated execution of the robot on the grid
- Optimized data structures (min-heap)

## Data Structures and Algorithms

- **Grid:** Grid representation featuring free cells, obstacles, packages, and the robot
- **Robot:** Tracks current position, remaining packages to collect, and complete route
- **Dijkstra:** Algorithm used to find the shortest path between two points
- **Heap:** Min-heap implementation used to optimize Dijkstra's algorithm

## Customization

You can adjust grid size, the number of packages, and obstacle density by modifying the configuration variables at the beginning of `main.c`.

## Author

Developed by Tierri Monteiro for the C Programming course, within the Collaborative Robotics and Industrial Intelligence program at Instituto Politécnico do Cávado e do Ave (IPCA).
