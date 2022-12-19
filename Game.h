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
		loadGameBoard();
	}
	~Game()
	{
		ImGui::SFML::Shutdown();
	}

	void run();
	void render();
	void update();
	void handleEvents();
	void initOptionMenu();



private:
	void loadGameBoard();
	int getLiveNeighbors(int x, int y);

private:
	sf::RenderWindow m_window;
	bool m_startGame = false;
	int grid_width = 70;
	int grid_height = 50;

	// Game board state
	std::vector<std::vector<bool>> grid;

	// Cell size, in pixels
	int cell_size = 10;

	int generation_counter = 0;
	bool remain_cell_alive = true;
	int pauseGeneration = 200;
};
