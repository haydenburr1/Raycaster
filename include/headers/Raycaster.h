#pragma once
#include "Globals.h"
#include <SFML/Graphics.hpp>

class Raycaster
{
public:
    Raycaster(sf::RenderWindow& window, sf::Sprite& sprite, float& theta, float& verticalAngle);
    void drawRays();

private:
    sf::Vector2f castRay(float deltaTheta) const;

    sf::RenderWindow& m_window; // Pass by reference
    sf::Sprite& m_sprite;
    float& m_theta;
    float& m_verticalAngle;

    static constexpr float m_fov = 60.f;
    const int m_noOfRays;
    const float m_sliceWidth;

    sf::Texture m_wallTexture;
};
