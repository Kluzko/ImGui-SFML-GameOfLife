#include "Game.h"

void Game::run()
{
	sf::Clock deltaClock;
	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed)
				m_window.close();
		}
		ImGui::SFML::Update(m_window, deltaClock.restart());

		initOptionMenu();

		m_window.clear();
		ImGui::SFML::Render(m_window);
		m_window.display();
	}
}

void Game::initOptionMenu()
{
	ImGui::Begin("Option Menu");
	ImGui::Text("Window text!");
	ImGui::End();
}
