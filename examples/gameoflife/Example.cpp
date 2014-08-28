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
//// Game of life code, taken from https://github.com/ZwodahS/ncurses-gameoflife
struct Cell
{
    Cell(const int& x, const int& y)
        : x(x), y(y), aliveNow(false), aliveNext(false)
    {
    }
    const int x;
    const int y;
    bool aliveNow;
    bool aliveNext;
};

int modX[] = {-1, 0, 1, 1, 1, 0, -1, -1};
int modY[] = {-1, -1, -1, 0, 1, 1, 1, 0};
int speed[] = {300, 200, 100, 50, 25};
int countAlive(std::vector<std::vector<Cell*> >& cells, Cell& cell, const int& width, const int& height)
{
    int count = 0;
    for (int i = 0; i < 8; i++)
    {
        int x = modX[i] + cell.x;
        int y = modY[i] + cell.y;
        if ( x >= 0 && x < width && y >= 0 && y < height)
        {
            if (cells[x][y]->aliveNow)
            {
                count++;
            }
        }
    }
    return count;
}

void step(std::vector<std::vector<Cell*> >& cells, Cell& cell, const int& width, const int& height)
{
    int count = countAlive(cells, cell, width, height);
    if (cell.aliveNow)
    {
        if (count < 2 || count > 3)
        {
            cell.aliveNext = false;
        }
        else
        {
            cell.aliveNext = true;
        }
    }
    else
    {
        if (count == 3)
        {
            cell.aliveNext = true;
        }
    }
}

void updateCell(std::vector<std::vector<Cell*> >& cells, Cell& cell, const int& width, const int& height)
{
    cell.aliveNow = cell.aliveNext;
    cell.aliveNext = false;
}

void random(std::vector<std::vector<Cell*> >& cells, Cell& cell, const int& width, const int& height)
{
    cell.aliveNow = (rand() % 7 == 0) ? true : false;
}

void map(std::vector<std::vector<Cell*> >& cells, const int& width, const int& height, void (*apply)(std::vector<std::vector<Cell*> >& cells, Cell& cell, const int& width, const int& height) )
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            apply(cells, *cells[x][y], width, height);
        }
    }
}

////// end of gol

void Example::init(const std::string& title, const sf::Vector2i& boardSize, const sf::Vector2i& cellSize)
{
    this->title = title;
    this->boardSize = boardSize;
    this->cellSize = cellSize;
    this->screenSize.x = boardSize.x * cellSize.x;
    this->screenSize.y = boardSize.y * cellSize.y;
    window = new sf::RenderWindow(sf::VideoMode(screenSize.x, screenSize.y), title);
    window->setFramerateLimit(60);
    screen = new zf::Terminal(*window, boardSize);
    screen->init(cellSize, cellSize);
    
}

void Example::run()
{
    bool quit = false;
    sf::Clock clock;

    /**
     * Create a terminal window that occupies the entire screen.
     */
    zf::TermWindow* board = screen->newWindow(sf::IntRect(0, 0, boardSize.x, boardSize.y));

    /**
     * Loading of assets
     */
    sf::Texture texture;
    if (!texture.loadFromFile("data/font_32/special/fill.png"))
    {
        std::cout << "Fail to load image" << std::endl;
        return ;
    }
    sf::Sprite blackSprite(texture, sf::IntRect(0,0,cellSize.x,cellSize.y));
    blackSprite.setColor(sf::Color::Black);
    sf::Sprite whiteSprite(texture, sf::IntRect(0,0,cellSize.x,cellSize.y));
    whiteSprite.setColor(sf::Color::White);

    /// create the cells.
    std::vector<std::vector<Cell*> > cells;
    for (int x = 0; x < boardSize.x; x++)
    {
        std::vector<Cell*> columns;
        for (int y = 0; y < boardSize.y; y++)
        {
            columns.push_back(new Cell(x, y));
        }
        cells.push_back(columns);
    }
    
    float updateFrequency = 0.1;
    float timePassed = 0;

    /// initialize the cell to random value
    map (cells, boardSize.x, boardSize.y, random);


    while (!quit && window->isOpen())
    {
        sf::Time delta = clock.restart();
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

        if (!quit)
        {
            if (timePassed >= updateFrequency)
            {
                // update (lazy to put into their own method)
                map (cells, boardSize.x, boardSize.y, step);
                map (cells, boardSize.x, boardSize.y, updateCell);
                for (int x = 0; x < boardSize.x; x++)
                {
                    for (int y = 0; y < boardSize.y; y++)
                    {
                        board->putSprite_xyb(x, y, cells[x][y]->aliveNow ? whiteSprite : blackSprite);
                    }
                }
                timePassed -= updateFrequency;
            }
            draw(delta);
        }
    }
    for (int x = 0; x < boardSize.x; x++)
    {
        for (int y = 0; y < boardSize.y; y++)
        {
            delete cells[x][y];
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
