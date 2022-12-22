#pragma once
#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>


class Game
{
public:
	Game(unsigned int width, unsigned int height, const std::string& title)
		: m_window(sf::VideoMode(width, height), title)
	{
		ImGui::SFML::Init(m_window);

		// Initialize the game board with a random pattern of live and dead cells
		load_game_board();
	}
	~Game()
	{
		ImGui::SFML::Shutdown();
	}

	void run();
	void render();
	void update();
	void handle_events();
	void init_option_menu();

private:
	void load_game_board();
	int get_live_neighbors(int x, int y);

	void update_timer();

	sf::Vector2i calculate_grid_size();
	sf::Vector2i calculate_grid_position(const sf::Vector2i& grid_size);
private:
	sf::RenderWindow m_window;
	bool m_startGame = false;

	int m_grid_width = 70;
	int m_grid_height = 50;

	// Game board state
	std::vector<std::vector<bool>> m_grid;

	// Cell size, in pixels
	int m_cell_size = 10;

	// Elapsed time in simulation
	sf::Time m_elapsed_time = sf::Time::Zero;
	sf::Clock m_timer;
	bool m_timer_running = false;

	// Game options
	int m_generation_counter = 0;
	bool m_remain_cell_alive = true;
	int m_pause_generation = 200;
};
