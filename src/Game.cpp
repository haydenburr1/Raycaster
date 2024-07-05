#include "headers/Game.h"

Game::Game()
    : m_FPS(60),
    m_window(sf::VideoMode(WIDTH, HEIGHT), "Doom"),
    m_player(m_window),
    m_gunSprite(m_gunTexture),
    debugState(false),
    m_elapsedTime(0.0f),
    m_frameCount(0.0f)
{
    m_window.setFramerateLimit(m_FPS);

    // Initialize gun sprite
    if (!m_gunTexture.loadFromFile("images/DoomGun.png")) {
        // Handle loading error
        std::cerr << "Failed to load gun texture." << std::endl;
    }

    m_gunSprite.setScale(sf::Vector2f(2.f, 2.f));
    m_gunSprite.setOrigin(sf::Vector2f(static_cast<float>(m_gunTexture.getSize().x) / 2.f, m_gunTexture.getSize().y / 2.f));
    m_gunSprite.setPosition(static_cast<float>(WIDTH / 2), static_cast<float>(HEIGHT / 2));
}

void Game::run()
{


    // Clock to track frame time
    while (m_window.isOpen())
    {
        eventLoop();

        m_window.clear(sf::Color::Cyan);

#if FLAT
        drawLines();
        drawBoxes();
#endif

        m_player.run();
        initFps();

        m_window.display();

    }
}

void Game::initFps()
{
    m_frameCount++;

    m_elapsedTime += m_clock.restart().asSeconds();

    if (m_elapsedTime >= 1.f)
    {
        float fps = m_frameCount / m_elapsedTime;

        std::string strFps = "Doom - FPS: " + std::to_string(fps);

        m_window.setTitle(strFps);

        // Reset for the next second
        m_elapsedTime = 0.f;
        m_frameCount = 0;
    }
}

void Game::eventLoop()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_window.close();
    }
}

void Game::drawLines()
{
    for (int x = 0; x < WIDTH; x += GRID_SIZE)
    {
        sf::Vertex verticalLine[] =
        {
            sf::Vertex(sf::Vector2f(x, 0), sf::Color::Red),
            sf::Vertex(sf::Vector2f(x, HEIGHT), sf::Color::Red)
        };
        m_window.draw(verticalLine, 2, sf::Lines);
    }

    for (int y = 0; y < HEIGHT; y += GRID_SIZE)
    {
        sf::Vertex horizontalLine[] =
        {
            sf::Vertex(sf::Vector2f(0, y), sf::Color::Red),
            sf::Vertex(sf::Vector2f(WIDTH, y), sf::Color::Red)
        };
        m_window.draw(horizontalLine, 2, sf::Lines);
    }
}

void Game::drawBoxes()
{
    for (int x = 0; x < HEIGHT / GRID_SIZE; ++x)
    {
        for (int y = 0; y < WIDTH / GRID_SIZE; ++y)
        {
            if (map[x][y] == 1)
            {
                sf::RectangleShape rectangle(sf::Vector2f(GRID_SIZE, GRID_SIZE));
                rectangle.setPosition(y * GRID_SIZE, x * GRID_SIZE);
                rectangle.setFillColor(sf::Color::Blue);
                m_window.draw(rectangle);
            }
        }
    }
}