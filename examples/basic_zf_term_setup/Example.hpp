#ifndef _EXAMPLE_HPP_
#define _EXAMPLE_HPP_
#include <SFML/Graphics.hpp>
#include <string>
#include "z_framework/zf_term.hpp"
class Example
{
public:
    Example();
    ~Example();

    void init(const std::string& title, const sf::Vector2i& termSize, const sf::Vector2i& cellSize);
    void run();
    
    void update();
    void draw(const sf::Time& delta);

private:
    std::string title;
    sf::RenderWindow* window;
    zf::TermScreen* screen;

    sf::Vector2i termSize;
    sf::Vector2i cellSize;
    sf::Vector2i screenSize;    
};
#endif
