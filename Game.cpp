#include "Game.h"

void Game::loadGameBoard()
{
	// Seed the random number generator
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 1);

	// Resize the grid vector and initialize its elements to random values
	grid.resize(120);
	for (auto& row : grid) {
		row.resize(120);
		for (auto cell : row) {
			cell = (dis(gen) == 1);
		}
	}
}

void Game::run()
{
	sf::Clock deltaClock;
	while (m_window.isOpen())
	{
		handleEvents();

		ImGui::SFML::Update(m_window, deltaClock.restart());

		initOptionMenu();
		// Update the game
		update();

		m_window.clear();
		render();
		ImGui::SFML::Render(m_window);
		m_window.display();
	}
}

void Game::render()
{
	// Get the size of the window
	int window_width = m_window.getSize().x;
	int window_height = m_window.getSize().y;

	// Calculate the aspect ratio of the grid
	float grid_aspect_ratio = static_cast<float>(grid_width) / grid_height;

	// Calculate the aspect ratio of the window
	float window_aspect_ratio = static_cast<float>(window_width) / window_height;

	// Set the size of the cells based on the window size and the number of cells
	cell_size = std::min(window_width / grid_width, window_height / grid_height);

	// Calculate the width and height of the grid in pixels
	int grid_width_pixels = grid_width * cell_size;
	int grid_height_pixels = grid_height * cell_size;

	// Calculate the top-left corner of the grid based on the window size and grid size
	int grid_x = (window_width - grid_width_pixels) / 2;
	int grid_y = (window_height - grid_height_pixels) / 2;


	sf::RectangleShape cell(sf::Vector2f(cell_size, cell_size));
	cell.setOutlineThickness(1.0f);
	cell.setOutlineColor(sf::Color::Black);

	for (int i = 0; i < grid_width; i++)
	{
		for (int j = 0; j < grid_height; j++)
		{
			// Set the cell's position
			cell.setPosition(grid_x + i * cell_size, grid_y + j * cell_size);

			// Set the cell's fill color based on its state
			if (grid[i][j])
			{
				cell.setFillColor(sf::Color::Black);
			}
			else
			{
				cell.setFillColor(sf::Color::White);
			}

			// Draw the cell
			m_window.draw(cell);
		}
	}
}


void Game::update()
{
	if (!m_startGame)
	{
		return;
	}

	// Create a copy of the game board to store the new state of the cells
	std::vector<std::vector<bool>> new_grid = grid;

	// Iterate through the grid and update the state of each cell
	for (int x = 0; x < grid_width; x++)
	{
		for (int y = 0; y < grid_height; y++)
		{
			// Get the number of live neighbors of the current cell
			int live_neighbors = getLiveNeighbors(x, y);

			// Update the state of the current cell based on the number of live neighbors
			if (grid[x][y])
			{
				// Any live cell with fewer than two live neighbors dies, as if by underpopulation.
				// Any live cell with more than three live neighbors dies, as if by overpopulation.
				if (live_neighbors < 2 || live_neighbors > 3)
				{
					new_grid[x][y] = false;
				}
			}
			else
			{
				// Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
				if (live_neighbors == 3)
				{
					new_grid[x][y] = true;
				}
			}
		}
	}

	// Update the game board with the new state of the cells
	grid = new_grid;
}

int Game::getLiveNeighbors(int x, int y)
{
	int live_neighbors = 0;

	// Check the top-left neighbor
	if (x > 0 && y > 0 && grid[x - 1][y - 1])
	{
		live_neighbors++;
	}

	// Check the top neighbor
	if (y > 0 && grid[x][y - 1])
	{
		live_neighbors++;
	}

	// Check the top-right neighbor
	if (x < grid_width - 1 && y > 0 && grid[x + 1][y - 1])
	{
		live_neighbors++;
	}

	// Check the left neighbor
	if (x > 0 && grid[x - 1][y])
	{
		live_neighbors++;
	}

	// Check the right neighbor
	if (x < grid_width - 1 && grid[x + 1][y])
	{
		live_neighbors++;
	}

	// Check the bottom-left neighbor
	if (x > 0 && y < grid_height - 1 && grid[x - 1][y + 1])
	{
		live_neighbors++;
	}

	// Check the bottom neighbor
	if (y < grid_height - 1 && grid[x][y + 1])
	{
		live_neighbors++;
	}

	// Check the bottom-right neighbor
	if (x < grid_width - 1 && y < grid_height - 1 && grid[x + 1][y + 1])
	{
		live_neighbors++;
	}

	return live_neighbors;
}

void Game::handleEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(event);
		if (event.type == sf::Event::Closed)
			m_window.close();
	}
}



void Game::initOptionMenu()
{
	ImGui::Begin("Option Menu");

	ImGui::Text("Game state");
	if (ImGui::Button(m_startGame ? "Stop" : "Start")) {
		m_startGame = !m_startGame;
	}

	ImGui::Separator();
	if (!m_startGame) {
		ImGui::Text("Game board settings");
		if (ImGui::SliderInt("Grid width", &grid_width, 60, 120) || ImGui::SliderInt("Grid height", &grid_height, 40, 120)) {
			loadGameBoard();
		}
	}
	else {
		ImGui::Text("Stop the game to change settings");
	}

	// Calculate the new size of the cells based on the grid size and window size
	int window_width = m_window.getSize().x;
	int window_height = m_window.getSize().y;
	cell_size = std::min(window_width / grid_width, window_height / grid_height);

	ImGui::End();
}