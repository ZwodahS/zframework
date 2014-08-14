#include <stdlib.h>
#include <time.h>
#include "Example.hpp"
int main(int argc , char * argv[])
{
    srand(time(NULL));
    
    Example e;
    e.init("Example", sf::IntRect(0, 0, 800, 600));
    e.run();
}
