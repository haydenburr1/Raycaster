#include "headers/Raycaster.h"
#include <iostream>

Raycaster::Raycaster(sf::RenderWindow& window, sf::Sprite& sprite, float& theta, float& verticalAngle)
        : m_window(window),
        m_sprite(sprite),
        m_theta(theta),
        m_noOfRays(3000),
        m_sliceWidth(static_cast<float>(WIDTH) / m_noOfRays),
        m_verticalAngle(verticalAngle)
    {
        m_wallTexture.loadFromFile("../../images/wallTexture.png");
        m_wallTexture.setRepeated(true);
    }

sf::Vector2f Raycaster::castRay(float deltaTheta) const
{
    sf::Vector2f rayPos = m_sprite.getPosition();

    float stepSize = 1.f;

    while (true) {
        rayPos.x += std::cos(-deltaTheta) * stepSize;
        rayPos.y += std::sin(-deltaTheta) * stepSize;

        if (checkRayCollisions(rayPos)) {
            return rayPos;
        }

        // Handle case where ray goes out of bounds
        if (rayPos.x < 0 || rayPos.x >= WIDTH || rayPos.y < 0 || rayPos.y >= HEIGHT) {
            return rayPos;  // Return the last valid position
        }
    }
}

bool Raycaster::checkRayCollisions(const sf::Vector2f& rayPos) const
{
    int gridX = static_cast<int>(rayPos.x / GRID_SIZE);
    int gridY = static_cast<int>(rayPos.y / GRID_SIZE);

    if (gridX < 0 || gridY < 0 || gridX >= MAP_WIDTH || gridY >= MAP_HEIGHT) {
        return true;
    }

    return map[gridY][gridX] == 1;
}

void Raycaster::drawRays()
{   
    
        float startAngle = m_theta - (m_fov / 2.f) * (PI / 180);
        float endAngle = m_theta + (m_fov / 2.f) * (PI / 180);
        float angleIncrement = (endAngle - startAngle) / m_noOfRays;

        for (float deltaTheta = startAngle, screenX = 0; deltaTheta <= endAngle; deltaTheta += angleIncrement, screenX += m_sliceWidth)
        {
            sf::Vector2f rayEndVector = castRay(deltaTheta);

            /*sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(m_sprite.getPosition()), sf::Color::Red),
                sf::Vertex(rayEndVector, sf::Color::Red)
            };
            m_window.draw(line, 2, sf::Lines);
            */

            double distance = std::sqrt(std::pow(rayEndVector.x - m_sprite.getPosition().x, 2) + std::pow(rayEndVector.y - m_sprite.getPosition().y, 2)) * std::cos(m_theta - deltaTheta);

            double lineHeight = (GRID_SIZE * HEIGHT) / distance;

            float LineTop = static_cast<float>((HEIGHT / 2.f) - (lineHeight / 2.f)) + m_verticalAngle;
            float lineBottom = static_cast<float>(LineTop + lineHeight) ;

            float screenCenter = static_cast<float>(WIDTH) / 2 ;
            float screenXCentered = screenCenter + (screenX - screenCenter);

            sf::VertexArray wall(sf::Quads, 4);

            wall[0].position = sf::Vector2f(screenXCentered, LineTop);
            wall[1].position = sf::Vector2f(screenXCentered, lineBottom);
            wall[2].position = sf::Vector2f(screenXCentered + m_sliceWidth, lineBottom);
            wall[3].position = sf::Vector2f(screenXCentered + m_sliceWidth, LineTop);

            float texCoordX;

            if (abs(rayEndVector.x - GRID_SIZE * round(rayEndVector.x / GRID_SIZE)) < abs(rayEndVector.y - GRID_SIZE * round(rayEndVector.y / GRID_SIZE)))
            {
                texCoordX = rayEndVector.y - GRID_SIZE * floor(rayEndVector.y / GRID_SIZE);

                wall[0].color = sf::Color(255, 0, 0);
                wall[1].color = sf::Color(255, 0, 0);
                wall[2].color = sf::Color(255, 0, 0);
                wall[3].color = sf::Color(255, 0, 0);
            }
            else
            {
                texCoordX = GRID_SIZE * ceil(rayEndVector.x / GRID_SIZE) - rayEndVector.x;
                wall[0].color = sf::Color(100, 0, 0);
                wall[1].color = sf::Color(100, 0, 0);
                wall[2].color = sf::Color(100, 0, 0);
                wall[3].color = sf::Color(100, 0, 0);
            }

            wall[0].texCoords = sf::Vector2f(texCoordX, 0.f);
            wall[1].texCoords = sf::Vector2f(texCoordX, static_cast<float>(m_wallTexture.getSize().y));
            wall[2].texCoords = sf::Vector2f(texCoordX + m_sliceWidth, static_cast<float>(m_wallTexture.getSize().y));
            wall[3].texCoords = sf::Vector2f(texCoordX + m_sliceWidth, 0);
            
            // Set texture
            sf::RenderStates states;
            states.texture = &m_wallTexture;   

            m_window.draw(wall, states);
        }
}
