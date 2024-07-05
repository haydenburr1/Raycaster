#include "headers/Player.h"
#include "headers/Utils.h"

Player::Player(sf::RenderWindow& window)
    : m_velocity(5),
    m_scaleFactor(6.0f),
    m_window(window),
    m_theta(0.0f),
    m_previousPos(m_playerSprite.getPosition()),
    m_raycaster(window, m_playerSprite, m_theta, m_verticalAngle),
    m_verticalAngle(0),
    mousePos(sf::Mouse::getPosition())
{
    m_playerTexture.loadFromFile("images/MapPlayer16.png");

    m_playerSprite.setTexture(m_playerTexture);
    m_playerSprite.setScale(m_scaleFactor, m_scaleFactor);
    m_playerSprite.setPosition(static_cast<float>(WIDTH) / 2, static_cast<float>(HEIGHT) / 2);
    m_playerSprite.setOrigin(sf::Vector2f(static_cast<float>(m_playerTexture.getSize().y) / 2.f, static_cast<float>(m_playerTexture.getSize().y) / 2.f));
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
    // Handle keyboard inputs for player rotation and movement

    // Movement forward (W) and backward (S)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        futurePos.x = std::cos(-m_theta) * m_velocity;
        futurePos.y = std::sin(-m_theta) * m_velocity;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        futurePos.x = -std::cos(-m_theta) * m_velocity;
        futurePos.y = -std::sin(-m_theta) * m_velocity;
    }

    // Movement left (Left Arrow) and right (Right Arrow)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        futurePos.x = std::cos(-m_theta - (90 * (180 / PI))) * m_velocity;
        futurePos.y = std::sin(-m_theta - (90 * (180 / PI))) * m_velocity;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        futurePos.x = -std::cos(-m_theta - (90 * (180 / PI))) * m_velocity;
        futurePos.y = -std::sin(-m_theta - (90 * (180 / PI))) * m_velocity;
    }

    // Adjust vertical angle with Up and Down arrow keys
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
        m_verticalAngle += m_velocity * 4;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        m_verticalAngle -= m_velocity * 4;
    }

    // Calculate the new position based on future position adjustments
    sf::Vector2f newPosition = m_playerSprite.getPosition() + futurePos;

    // Check for collisions and update player position accordingly
    if (!Utils::checkRayCollisions(newPosition))
    {
        m_playerSprite.setPosition(newPosition);
    }

    else {
        if (!Utils::checkRayCollisions(sf::Vector2f(newPosition.x, m_playerSprite.getPosition().y)))
        {
            m_playerSprite.setPosition(newPosition.x, m_playerSprite.getPosition().y);
        }
        if (!Utils::checkRayCollisions(sf::Vector2f(m_playerSprite.getPosition().x, newPosition.y)))
        {
            m_playerSprite.setPosition(m_playerSprite.getPosition().x, newPosition.y);
        }
    }

    collisions(futurePos);

    // Ensure angles remain within valid ranges
    wrapTheta();
}

void Player::collisions(sf::Vector2f futurePos)
{
    sf::Vector2f newPosition = m_playerSprite.getPosition() + futurePos;

    // Check for collisions and update player position accordingly
    if (!Utils::checkRayCollisions(newPosition))
    {
        m_playerSprite.setPosition(newPosition);
    }

    else {
        if (!Utils::checkRayCollisions(sf::Vector2f(newPosition.x, m_playerSprite.getPosition().y)))
        {
            m_playerSprite.setPosition(newPosition.x, m_playerSprite.getPosition().y);
        }
        if (!Utils::checkRayCollisions(sf::Vector2f(m_playerSprite.getPosition().x, newPosition.y)))
        {
            m_playerSprite.setPosition(m_playerSprite.getPosition().x, newPosition.y);
        }
    }
}

void Player::mouseControls()
{
    sf::Vector2f futurePos(0.f, 0.f);
    // Get the current mouse position relative to the window
    sf::Vector2i mouseCurrentPos = sf::Mouse::getPosition(m_window);
    sf::Vector2i windowCenter = sf::Vector2i(static_cast<float>(WIDTH / 2), static_cast<float>(HEIGHT / 2.f));

    // Calculate the change in mouse position (delta)
    sf::Vector2i mouseDelta = mouseCurrentPos - windowCenter;

    // Update theta and verticalAngle based on mouse movement
    m_theta += 0.002f * mouseDelta.x;  // Sensitivity factor for horizontal rotation
    m_verticalAngle += 0.002f * mouseDelta.y;  // Sensitivity factor for vertical rotation

    // Keep vertical angle within a certain range
    //m_verticalAngle = std::max(-1.57f, std::min(1.57f, m_verticalAngle));  // -90 to +90 degrees in radians

    // Reset mouse position to the center of the window
    sf::Mouse::setPosition(windowCenter, m_window);
}

void Player::buttonControls()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        m_theta -= 0.05f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        m_theta += 0.05f;
    }
}

void Player::run()
{
    controls();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        buttonControls();
    }
    else
    {
        mouseControls();
    }

    //chooseFrame();
    drawFloors();
    m_raycaster.drawRays();
#if FLAT
    m_window.draw(m_playerSprite);
#endif
}

// TODO
void Player::drawFloors()
{

}
