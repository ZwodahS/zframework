#include <stdlib.h>
#include <time.h>
#include "Example.hpp"
int main(int argc , char * argv[])
{
    srand(time(NULL));
    
    Example e;
    e.init("Example", sf::Vector2i(81, 52), sf::Vector2i(16, 16));
    e.run();
}
