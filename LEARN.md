# Introduction to Game of Life

The Game of Life is a cellular automaton simulation developed by mathematician John Horton Conway in 1970. 
It simulates the evolution of a population of cells on a two-dimensional grid over time.

Each cell in the grid is either "alive" or "dead", and its state is determined by the states of its neighbors according to a set of simple rules.
Over time, the cells interact and change state, producing patterns and structures that can be surprisingly complex and dynamic.

# Understanding the Code

The Game of Life simulation is implemented using C++ and the SFML and ImGui libraries.

- SFML is used for rendering the simulation on the screen, while ImGui is used for creating the user interface.
- The simulation is controlled by the GameOfLife class, which implements the rules of the simulation and updates the state of the grid over time.
- The **main** function creates an instance of the **GameOfLife** class and starts the simulation.

# Running the Project

To run the Game of Life simulation:

1. Clone the repository: git clone https://github.com/Kluzko/ImGui-SFML-GameOfLife.git
2. Open the SFML.sln file in Visual Studio.
3. Build and run the project.

# Exploring the Code

To learn more about the Game of Life simulation and how it works, you can start by exploring the code in the following files:

- **GameOfLife.h**: Contains the declaration of the GameOfLife class, which implements the rules of the simulation and updates the state of the grid.
- **GameOfLife.cpp**: Contains the implementation of the GameOfLife class.
- **main.cpp**: Contains the main function, which creates an instance of the **GameOfLife** class and starts the simulation.

# Contributing

If you want to contribute to this project, feel free to submit a pull request. All contributions are welcome, whether they are bug fixes, new features, or just improvements to the codebase.

# License
This project is licensed under the MIT License - see the [LICENSE](https://github.com/Kluzko/ImGui-SFML-GameOfLife/blob/master/LICENSE) file for details.
