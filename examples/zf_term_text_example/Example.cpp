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
    screen = new zf::TermScreen(*window, termSize);
    screen->init(cellSize, sf::Vector2i(32, 32));
    screen->autoLoad("data/font_32");
}

void Example::run()
{
    bool quit = false;
    sf::Clock clock;

    /**
     * Create a terminal window that occupies the entire screen.
     */
    zf::TermWindow& board = screen->newWindow(sf::IntRect(0, 0, termSize.x, termSize.y));
    
    
    int frame = 0;
    float timePassed = 0;
    while (!quit && window->isOpen())
    {
        sf::Time delta = clock.restart();
        frame++;
        timePassed += delta.asSeconds();
        
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
                quit = true;
            }
        }
        int row = 1, col = 1;
        board.putString_xy(1, 1, std::string(1, char(32)));
        for (int i = 33; i < 127; i++)
        {
            board.putString_xy(col, row, std::string(1, char(i)));
            col++;
            if (col == termSize.x - 2)
            {
                col = 1;
                row++;
            }
        }

        for (int i = 0; i < zf::TotalSpecialChar; i++)
        {
            board.putSprite_xyb(col, row, screen->getSpecialChar(i).createSprite());
            col++;
            if (col == termSize.x - 2)
            {
                col = 1;
                row++;
            }
        }
        board.drawCenterBorder();

        row++;
        board.putString_xy(1, ++row, std::to_string(timePassed));
        board.putString_xy(1, ++row, std::to_string(frame / timePassed));
        board.putString_xy(1, ++row, std::to_string(1 / delta.asSeconds()));

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
