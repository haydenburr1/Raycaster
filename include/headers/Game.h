#pragma once
#include "Player.h"

class Game
{
public:
	Game();

	void run();
	void setDebugState(bool state);

private:
	void eventLoop();
	void drawBoxes();
	void drawLines();

	const int m_FPS;
	bool debugState;

	sf::RenderWindow m_window;
	Player m_player;
	sf::Texture m_gunTexture;
	sf::Sprite m_gunSprite;

};

