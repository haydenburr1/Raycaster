#pragma once
#include <cmath>
#include <iostream>
#include "Globals.h"
#include "Raycaster.h"

class Player {
public:
    Player(sf::RenderWindow& window);
    void run();

private:
    bool checkMapCollision(float newPosX, float newPosY);
    void draw() const;
    void chooseFrame();
    float wrapTheta();
    void controls();
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
