#include "Example.hpp"

Example::Example()
    : title("untitled"), window(nullptr)
{
}

Example::~Example()
{
    if (window)
    {
        delete window;
    }
}

void Example::init(const std::string& title, const sf::IntRect& size)
{
    this->title = title;
    window = new sf::RenderWindow(sf::VideoMode(size.width, size.height), title);
    window->setFramerateLimit(60);
    
}

void Example::run()
{
    bool quit = false;
    sf::Clock clock;
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

        if (!quit)
        {
            update();
            draw();
        }
    }
}

void Example::update()
{
}

void Example::draw()
{
    window->clear(sf::Color(20, 20, 20, 255));
    // other draw code comes here.
    window->display();
}
