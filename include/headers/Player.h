#pragma once
#include <cmath>
#include <iostream>
#include "Globals.h"
#include "Raycaster.h"
#include <SFML/Graphics.hpp>

class Player {
public:
    Player(sf::RenderWindow& window);
    void run();

private:
    void chooseFrame();
    float wrapTheta();
    void controls();
    void collisions(sf::Vector2f futurePos);
    void mouseControls();
    void buttonControls();
    void drawFloors();
    float wrapVerticalAngle();

    const float m_velocity;
    const float m_scaleFactor;
    float m_theta;
    float m_verticalAngle;

    sf::RenderWindow& m_window;
    sf::Texture m_playerTexture;
    sf::Vector2f m_previousPos;
    sf::Sprite m_playerSprite;

    Raycaster m_raycaster;

    sf::Vector2i mousePos;
};
