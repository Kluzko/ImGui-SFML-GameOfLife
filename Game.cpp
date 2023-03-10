#include "Game.h"

void Game::load_game_board()
{
	// Seed the random number generator
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 1);

	// Resize the grid vector and initialize its elements to random values
	m_grid.resize(120);
	for (auto& row : m_grid) {
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
		handle_events();

		ImGui::SFML::Update(m_window, deltaClock.restart());

		init_option_menu();
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
	// Calculate the dimensions and position of the grid
	sf::Vector2i grid_size = calculate_grid_size();
	sf::Vector2i grid_position = calculate_grid_position(grid_size);


	sf::RectangleShape cell(sf::Vector2f(m_cell_size, m_cell_size));
	cell.setOutlineThickness(1.0f);
	cell.setOutlineColor(sf::Color::Black);


	for (int i = 0; i < m_grid_width; i++)
	{
		for (int j = 0; j < m_grid_height; j++)
		{
			// Set the cell's position
			float cell_x = static_cast<float>(grid_position.x + i * m_cell_size);
			float cell_y = static_cast<float>(grid_position.y + j * m_cell_size);

			cell.setPosition(cell_x, cell_y);
			// Set the cell's fill color based on its state
			cell.setFillColor(m_grid[i][j] ? sf::Color::Black : sf::Color::White);
			// Draw the cell
			m_window.draw(cell);
		}
	}
}

void Game::update()
{

	update_timer();

	if (!m_startGame)
	{
		return;
	}

	if (!m_remain_cell_alive && m_generation_counter >= m_pause_generation) {
		m_startGame = false;
		return;
	}

	// Create a copy of the game board to store the new state of the cells
	std::vector<std::vector<bool>> new_grid = m_grid;

	// Iterate through the grid and update the state of each cell
	for (int x = 0; x < m_grid_width; x++)
	{
		for (int y = 0; y < m_grid_height; y++)
		{
			// Get the number of live neighbors of the current cell
			int live_neighbors = get_live_neighbors(x, y);

			// Update the state of the current cell based on the number of live neighbors
			if (m_grid[x][y])
			{
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
	m_grid = std::move(new_grid);
	m_generation_counter++;
}

int Game::get_live_neighbors(int x, int y)
{
	int live_neighbors = 0;
	int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

	for (int i = 0; i < 8; i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (nx >= 0 && ny >= 0 && nx < m_grid_width && ny < m_grid_height && m_grid[nx][ny])
		{
			live_neighbors++;
		}
	}

	return live_neighbors;
}

void Game::update_timer()
{

	if (m_startGame && !m_timer_running) {
		m_timer.restart();
		m_timer_running = true;
	}

	if (!m_startGame && m_timer_running) {
		m_timer_running = false;
	}

	// Update the elapsed time 
	if (m_timer_running) {
		m_elapsed_time += m_timer.getElapsedTime();
		m_timer.restart();
	}
}

sf::Vector2i Game::calculate_grid_size()
{
	// Calculate the aspect ratio of the grid
	float grid_aspect_ratio = static_cast<float>(m_grid_width) / m_grid_height;

	// Calculate the width and height of the grid in pixels
	int grid_width_pixels = m_grid_width * m_cell_size;
	int grid_height_pixels = m_grid_height * m_cell_size;

	return sf::Vector2i(grid_width_pixels, grid_height_pixels);
}

sf::Vector2i Game::calculate_grid_position(const sf::Vector2i& grid_size)
{
	// Get the size of the window
	int window_width = m_window.getSize().x;
	int window_height = m_window.getSize().y;

	// Calculate the top-left corner of the grid based on the window size and grid size
	int grid_x = (window_width - grid_size.x) / 2;
	int grid_y = (window_height - grid_size.y) / 2;

	return sf::Vector2i(grid_x, grid_y);
}

void Game::handle_events()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(event);
		if (event.type == sf::Event::Closed)
			m_window.close();
	}
}

void Game::init_option_menu()
{
	ImGui::Begin("Option Menu");

	ImGui::Text("Game state");

	if (ImGui::Button(m_startGame ? "Stop" : "Start")) {
		m_startGame = !m_startGame;
	}
	ImGui::SameLine();
	if (!m_startGame) {
		if (ImGui::Button("Reset grid")) {
			m_generation_counter = 0;
			m_elapsed_time = sf::Time::Zero;
			load_game_board();
		}
	}

	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();

	if (!m_startGame) {
		ImGui::Text("Game board settings");
		if (ImGui::SliderInt("Grid width", &m_grid_width, 60, 120) || ImGui::SliderInt("Grid height", &m_grid_height, 40, 120)) {
			load_game_board();
		}
		ImGui::Spacing();
		ImGui::Checkbox("Allow cells remain alive", &m_remain_cell_alive);
		ImGui::Spacing();
		if (!m_remain_cell_alive) {
			if (m_generation_counter > 1) {
				m_generation_counter = 0;
				m_elapsed_time = sf::Time::Zero;
				load_game_board();
			}

			ImGui::Text("Choose how many generations will be simulated");
			ImGui::SliderInt("Generation", &m_pause_generation, 200, 100000);
		}
	}
	else {
		ImGui::Text("Stop the game to change settings");
		ImGui::Text("Generation: %d", m_generation_counter);

		int seconds = static_cast<int>(m_elapsed_time.asSeconds());
		int minutes = seconds / 60;
		seconds %= 60;

		ImGui::Text("Elapsed time: %02d:%02d", minutes, seconds);
	}

	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();

	if (ImGui::Button("Show Game rules")) {
		ImGui::OpenPopup("Show Game rules");
	}

	if (ImGui::BeginPopupModal("Show Game rules", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("Conway's Game of Life is a cellular automaton game created by John Horton Conway in 1970.\nThe game is played on a grid of cells, where each cell can be either alive or dead. \nThe state of the cells is determined by a set of rules that determine how the cells evolve \nfrom one generation to the next. The rules are as follows:\n\n- Any live cell with two or three live neighbors survives to the next generation.\n- Any dead cell with exactly three live neighbors becomes a live cell.\n- All other cells die or remain dead.");
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	ImGui::Spacing();

	// Calculate the new size of the cells based on the grid size and window size
	int window_width = m_window.getSize().x;
	int window_height = m_window.getSize().y;
	m_cell_size = std::min(window_width / m_grid_width, window_height / m_grid_height);

	ImGui::End();
}
