#include "Game.h"

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
			cell.setFillColor(sf::Color::White);
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
		ImGui::SliderInt("Grid width", &grid_width, 60, 120);
		ImGui::SliderInt("Grid height", &grid_height, 60, 120);
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
