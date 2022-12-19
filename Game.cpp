#include "Game.h"

void Game::loadGameBoard()
{
	// Resize the grid
	grid.resize(grid_width, std::vector<bool>(grid_height));

	// Seed the random number generator
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 1);

	// Iterate through the grid and set each cell to a random state
	for (int x = 0; x < grid_width; x++)
	{
		for (int y = 0; y < grid_height; y++)
		{
			grid[x][y] = (dis(gen) == 1);
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

		m_window.clear();
		render();
		ImGui::SFML::Render(m_window);
		m_window.display();
	}
}

void Game::render()
{
	int grid_width_pixels = grid_width * cell_size;
	int grid_height_pixels = grid_height * cell_size;
	int window_width = m_window.getSize().x;
	int window_height = m_window.getSize().y;

	// Calculate the top-left corner of the grid based on the window size and grid size
	static int grid_x = 0;
	static int grid_y = 0;
	if (grid_x == 0 || grid_y == 0) {
		grid_x = (window_width - grid_width_pixels) / 2;
		grid_y = (window_height - grid_height_pixels) / 2;
	}

	for (int i = 0; i < grid_width; i++)
	{
		for (int j = 0; j < grid_height; j++)
		{
			sf::RectangleShape cell(sf::Vector2f(cell_size, cell_size));
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

			cell.setOutlineThickness(1.0f);
			cell.setOutlineColor(sf::Color::Black);

			m_window.draw(cell);
		}
	}
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
		if (
			ImGui::SliderInt("Grid width", &grid_width, 60, 120) ||
			ImGui::SliderInt("Grid height", &grid_height, 60, 120)) {
			// pass here load game board to avoid vector subscript out of range error
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
