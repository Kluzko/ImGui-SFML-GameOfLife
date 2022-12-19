# Welcome to the Game of Life project!

This project is an implementation of Conway's Game of Life using SFML for rendering and ImGui for user interface.

# Installation

To build and run the project, follow these steps:

1. Clone this repository.
2. Open the SFML.sln file in Visual Studio.
3. Build and run the project.

Note: These instructions are specific to Visual Studio. If you are using a different build system, you may need to adapt the instructions accordingly.

Too build this project im using [ImGui-SFML](https://github.com/eliasdaler/imgui-sfml) library which allows you to use Dear ImGui with SFML.

# Usage

To run the project, simply execute the compiled binary. The main window will appear, showing the Game of Life grid. 

To stop the simulation, click the "Stop" button in the toolbar on the right side of the window. To start the simulation again, click the "Start" button.

The toolbar also allows you to customize the appearance of the grid and control the simulation. 
You can use the toolbar to:

- Clear the grid: Click the "Reset grid" button to reset the grid to its initial state.
- Change the grid size: Use the slider to adjust the size of the grid.
- Set the number of generations: If you uncheck checkbox "Allow cells remain alive" the  number field will appear you can use it  to specify how many generations should be simulated before the simulation stops.

# Contributing

If you want to contribute to this project, feel free to submit a pull request. All contributions are welcome, whether they are bug fixes, new features, or just improvements to the codebase.

# License

This project is licensed under the MIT License - see the [LICENSE](https://github.com/Kluzko/ImGui-SFML-GameOfLife/blob/master/LICENSE) file for details.
