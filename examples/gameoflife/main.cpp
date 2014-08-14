#include <stdlib.h>
#include <time.h>
#include "Example.hpp"
int main(int argc , char * argv[])
{
    srand(time(NULL));
    
    Example e;
    e.init("Example", sf::Vector2i(200, 200), sf::Vector2i(4, 4));
    e.run();
}
