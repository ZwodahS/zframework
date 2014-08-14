#ifndef _EXAMPLE_HPP_
#define _EXAMPLE_HPP_
#include <SFML/Graphics.hpp>
#include <string>
class Example
{
public:
    Example();
    ~Example();

    void init(const std::string& title, const sf::IntRect& size);
    void run();
    
    void update();
    void draw();

private:
    std::string title;
    sf::RenderWindow* window;
};
#endif
