#pragma once
#include "Player.h"
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();

	void run();

private:
	void eventLoop();
	void drawBoxes();
	void drawLines();
	void initFps();

	const int m_FPS;
	bool debugState;

	sf::Clock m_clock;
	float m_elapsedTime;
	int m_frameCount;

	sf::RenderWindow m_window;
	Player m_player;
	sf::Texture m_gunTexture;
	sf::Sprite m_gunSprite;

};

