#include "headers/Player.h"

Player::Player(sf::RenderWindow& window)
    : m_velocity(7),
    m_scaleFactor(6.0f),
    m_window(window),
    m_theta(0.0f),
    m_previousPos(m_playerSprite.getPosition()),
    m_raycaster(window, m_playerSprite, m_theta, m_verticalAngle),
    m_verticalAngle(0),
    mousePos(sf::Mouse::getPosition())
{
    m_playerTexture.loadFromFile("../../images/MapPlayer16.png");

    m_playerSprite.setTexture(m_playerTexture);
    m_playerSprite.setScale(m_scaleFactor, m_scaleFactor);
    m_playerSprite.setPosition(static_cast<float>(WIDTH) / 2, static_cast<float>(HEIGHT) / 2);
    m_playerSprite.setOrigin(sf::Vector2f(static_cast<float>(m_playerTexture.getSize().y) / 2.f, static_cast<float>(m_playerTexture.getSize().y) / 2.f));
}

void Player::draw() const
{
    m_window.draw(m_playerSprite);
}

void Player::chooseFrame()
{
    float frame_angle = 360.f / (static_cast<float>(m_playerTexture.getSize().x) / m_playerTexture.getSize().y);
    int frame_index = static_cast<int>(std::floor(m_theta / frame_angle)) % static_cast<int>(m_playerTexture.getSize().x / m_playerTexture.getSize().y);

    // tank rendering and rotation
    m_playerSprite.setTextureRect(sf::IntRect(m_playerTexture.getSize().y * frame_index, 0, m_playerTexture.getSize().y, m_playerTexture.getSize().y));
    m_playerSprite.setRotation(-(m_theta * 180 / PI)); 
}

float Player::wrapTheta()
{
    m_theta = fmod(m_theta, 2 * PI);
    if (m_theta < 0)
    {
        m_theta += 2 * PI;
    }
    return m_theta;
}

void Player::controls()
{
    sf::Vector2f futurePos(0.f, 0.f);

    /*float direction_horizontal = 0;
    float direction_vertical = 0;

    unsigned short window_center_x = static_cast<unsigned short>(round(0.5f * m_window.getSize().x));
    unsigned short window_center_y = static_cast<unsigned short>(round(0.5f * m_window.getSize().y));

    m_theta = 60.f * -(window_center_x - sf::Mouse::getPosition(m_window).x) / m_window.getSize().x;
    m_verticalAngle = 60.f * (window_center_y - sf::Mouse::getPosition(m_window).y) / m_window.getSize().y;

    direction_horizontal = get_degrees(direction_horizontal + m_theta);
    //Putting 90 here breaks the game so I put 89.
    direction_vertical = std::max(-89.0f, std::min(89.0f, direction_vertical + m_theta));

    //Just so you know, this works even if the window is out of focus.
    //sf::Mouse::setPosition(sf::Vector2i(window_center_x, window_center_y), m_window);

    */

    // Handle keyboard inputs for player rotation and movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        m_theta -= 0.05f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        m_theta += 0.05f;
    }

    // Movement forward (W) and backward (S)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        futurePos.x = std::cos(-m_theta) * m_velocity;
        futurePos.y = std::sin(-m_theta) * m_velocity;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        futurePos.x = -std::cos(-m_theta) * m_velocity;
        futurePos.y = -std::sin(-m_theta) * m_velocity;
    }

    // Movement left (Left Arrow) and right (Right Arrow)
    // 1.5708f is approximately 90 degrees in radians
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        futurePos.x = std::cos(-m_theta + 1.5708f) * m_velocity;
        futurePos.y = std::sin(-m_theta + 1.5708f) * m_velocity;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        futurePos.x = -std::cos(-m_theta + 1.5708f) * m_velocity;
        futurePos.y = -std::sin(-m_theta + 1.5708f) * m_velocity;
    }

    // Adjust vertical angle with Up and Down arrow keys
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        m_verticalAngle += m_velocity * 4;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        m_verticalAngle -= m_velocity * 4;
    }

    // Calculate the new position based on future position adjustments
    sf::Vector2f newPosition = m_playerSprite.getPosition() + futurePos;

    // Check for collisions and update player position accordingly
    if (!checkMapCollision(newPosition.x, newPosition.y)) {
        m_playerSprite.setPosition(newPosition);
    }
    else {
        if (!checkMapCollision(newPosition.x, m_playerSprite.getPosition().y)) {
            m_playerSprite.setPosition(newPosition.x, m_playerSprite.getPosition().y);
        }
        if (!checkMapCollision(m_playerSprite.getPosition().x, newPosition.y)) {
            m_playerSprite.setPosition(m_playerSprite.getPosition().x, newPosition.y);
        }
    }

    // Ensure angles remain within valid ranges
    wrapTheta();
    wrapVerticalAngle();
}

float Player::wrapVerticalAngle()
{
    if (m_verticalAngle > 1000)
    {
        m_verticalAngle = 1000;
    }
    if (m_verticalAngle < -1000)
    {
        m_verticalAngle = -1000;
    }
    return m_verticalAngle;
}

void Player::run()
{
    controls();
    chooseFrame();
    drawFloors();
    m_raycaster.drawRays();
    // m_window.draw(m_playerSprite);
}

bool Player::checkMapCollision(float newPosX, float newPosY)
{
    int gridX = static_cast<int>(newPosX / GRID_SIZE);
    int gridY = static_cast<int>(newPosY / GRID_SIZE);

    if (gridX < 0 || gridY < 0 || gridX >= MAP_WIDTH || gridY >= MAP_HEIGHT)
    {
        return true;
    }

    return map[gridY][gridX] == 1;
}

void Player::drawFloors()
{
}
