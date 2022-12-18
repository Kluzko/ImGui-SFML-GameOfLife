#pragma once
#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game(std::size_t width, std::size_t height, const std::string& title)
		: m_window(sf::VideoMode(width, height), title)
	{
		ImGui::SFML::Init(m_window);
	}
	~Game()
	{
		ImGui::SFML::Shutdown();
	}

	void run();

	void initOptionMenu();

private:
	sf::RenderWindow m_window;
};
