#include "Example.hpp"
#include <iostream>
Example::Example()
    : title("Game of life"), window(nullptr)
{
}

Example::~Example()
{
    if (window)
    {
        delete window;
    }
}

void Example::init(const std::string& title, const sf::Vector2i& termSize, const sf::Vector2i& cellSize)
{
    this->title = title;
    this->termSize = termSize;
    this->cellSize = cellSize;
    this->screenSize.x = termSize.x * cellSize.x;
    this->screenSize.y = termSize.y * cellSize.y;
    window = new sf::RenderWindow(sf::VideoMode(screenSize.x, screenSize.y), title);
    window->setFramerateLimit(60);
    screen = new zf::Terminal(*window, termSize);
    screen->init(cellSize, sf::Vector2i(32, 32));
    
}

void Example::run()
{
    bool quit = false;
    sf::Clock clock;

    /**
     * Create a terminal window that occupies the entire screen.
     */
    zf::TermWindow* board = screen->newWindow(sf::IntRect(0, 0, termSize.x, termSize.y));

    /**
     * Loading of assets
     */
    sf::Texture texture;
    if (!texture.loadFromFile("data/fill.png"))
    {
        std::cout << "Fail to load image" << std::endl;
        return ;
    }
    sf::Sprite blackSprite(texture, sf::IntRect(0,0,cellSize.x,cellSize.y));
    blackSprite.setColor(sf::Color::Black);
    sf::Sprite whiteSprite(texture, sf::IntRect(0,0,cellSize.x,cellSize.y));
    whiteSprite.setColor(sf::Color::White);

    while (!quit && window->isOpen())
    {
        sf::Time delta = clock.restart();
        
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
                quit = true;
            }
        }
        
        board->putSprite_xyf(3, 3, blackSprite);
        board->putSprite_xyf(4, 4, whiteSprite); 

        if (!quit)
        {
            draw(delta);
        }
    }
}

void Example::update()
{
}

void Example::draw(const sf::Time& delta)
{
    window->clear(sf::Color(20, 20, 20, 255));
    screen->updateRenderWindow();
    window->display();
}
