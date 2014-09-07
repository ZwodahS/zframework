/*
 *           DO WHAT THE F*** YOU WANT TO PUBLIC LICENSE
 *                   Version 2, December 2004
 *
 * Copyright (C) 2014- ZwodahS(ericnjf@gmail.com)
 * zwodahs.github.io
 *
 * Everyone is permitted to copy and distribute verbatim or modified
 * copies of this license document, and changing it is allowed as long
 * as the name is changed.
 *
 *           DO WHAT THE F*** YOU WANT TO PUBLIC LICENSE
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *  0. You just DO WHAT THE F*** YOU WANT TO.
 *
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details.
 *
 * visit http://github.com/ZwodahS/zframework for the latest version
 */
#include "zf_twindow.hpp"
#include <iostream>
namespace zf
{
    const int TiledWindowFactory::NORTH_BIT = 1;
    const int TiledWindowFactory::EAST_BIT = 2;
    const int TiledWindowFactory::SOUTH_BIT = 4;
    const int TiledWindowFactory::WEST_BIT = 8;
    const int TiledWindowFactory::Border[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    const int TiledWindowFactory::Cross[16] = {16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
    const int TiledWindowFactory::Center_dot = 32;
    const int TiledWindowFactory::Alternate[2] = { 33, 34 };
    const int TiledWindowFactory::Up = 0;
    const int TiledWindowFactory::Right = 1;
    const int TiledWindowFactory::Down = 2;
    const int TiledWindowFactory::Left = 3;
    const int TiledWindowFactory::Arrow[4] = { 35, 36 , 37, 38 };
    const int TiledWindowFactory::Fill = 39;
    const int TiledWindowFactory::TotalSpecialChar = TiledWindowFactory::Fill + 1;
    const int TiledWindowFactory::TotalRequired = 127 - 32 + TiledWindowFactory::TotalSpecialChar;

    TiledWindowFactory::TiledWindowFactory()
        : imageSize(0), inited(false), texture(nullptr)
    {
    }

    TiledWindowFactory::~TiledWindowFactory()
    {
        for (auto window : windows)
        {
            delete window;
        }
    }

    void TiledWindowFactory::init(int imageSize, int maxRow, int maxCol)
    {
        if (inited)
        {
            return;
        }

        inited = true;
        this->imageSize = imageSize;
        ascii_starts = 0;
        ascii_ends = ascii_starts;

        const sf::Vector2i spritesheetSize(imageSize * maxCol, imageSize * maxRow);
        {
            texture = new sf::Texture();
            texture->create(spritesheetSize.x, spritesheetSize.y);
            spritesheet.create(texture, sf::IntRect(0, 0, spritesheetSize.x, spritesheetSize.y));
            int row = 0, col = 0;
            for (int i = 32; i < 127; i++)
            {
                auto region = spritesheet.createRegion(sf::IntRect(col * imageSize, row * imageSize, imageSize, imageSize));
                characters.push_back(region);
                col++;
                if (col == maxCol)
                {
                    col = 0;
                    row++;
                }
                ascii_ends++;
            }
            special_starts = ascii_ends;
            special_ends = special_starts;
            for (int i = 0; i < TotalSpecialChar; i++)
            {
                auto region = spritesheet.createRegion(sf::IntRect(col * imageSize, row * imageSize, imageSize, imageSize));
                specialCharacters.push_back(region);
                col++;
                if (col == maxCol)
                {
                    col = 0;
                    row++;
                }
                special_ends++;
            }
            while(row != maxRow)
            {
                // create all the spare location
                auto region = spritesheet.createRegion(sf::IntRect(col * imageSize, row * imageSize, imageSize, imageSize));
                specialCharacters.push_back(region);
                col++;
                if (col == maxCol)
                {
                    col = 0;
                    row++;
                }
            }
        }
    }

    TiledWindow* TiledWindowFactory::newWindow(const sf::Vector2i& _windowSize, int cellSize)
    {
        TiledWindow* window = new TiledWindow(*this);
        window->init(_windowSize, cellSize, imageSize);
        return window;
    }

    void TiledWindowFactory::freeWindow(TiledWindow* window)
    {
        if (!window)
        {
            return;
        }
        auto result = std::find(windows.begin(), windows.end(), window);
        if (result != windows.end())
        {
            windows.erase(result);
        }
        delete window;
    }

    std::vector<std::string> TiledWindowFactory::autoload(const std::string& path)
    {
        std::vector<std::string> errors;
        if (!texture)
        {
            return errors;
        }
        sf::Image image;

        /// basic ascii character
        for (int i = 32; i < 127; i++)
        {
            image.loadFromFile(path + "/basic/" + intToString(i) + ".png");
            if (!overrideCharImage(i, image))
            {
                errors.push_back(std::string("Fail to add char ") + char(i));
            }
        }
        std::vector<std::string> extendedLoadStrings;
        for (int i = 0; i < 16; i++)
        {
            extendedLoadStrings.push_back("border_" + intToString(i) + ".png");
        }
        for (int i = 0; i < 16; i++)
        {
            extendedLoadStrings.push_back("cross_" + intToString(i) + ".png");
        }
        extendedLoadStrings.push_back("center_dot.png");
        extendedLoadStrings.push_back("alternate_1.png");
        extendedLoadStrings.push_back("alternate_2.png");
        extendedLoadStrings.push_back("arrow_up.png");
        extendedLoadStrings.push_back("arrow_right.png");
        extendedLoadStrings.push_back("arrow_down.png");
        extendedLoadStrings.push_back("arrow_left.png");
        extendedLoadStrings.push_back("fill.png");
        for (int i = 0; i < extendedLoadStrings.size(); i++)
        {
            image.loadFromFile(path + "/special/" + extendedLoadStrings[i]);
            if (!addSpecialCharImage(i, image))
            {
                errors.push_back("Fail to add special char /special/" + extendedLoadStrings[i]);
            }
        } 
        return errors;
    }

    bool TiledWindowFactory::overrideCharImage(char c, const sf::Image& image)
    {
        TextureRegion charRegion = getChar(c);
        if (charRegion.texture)
        {
            spritesheet.addImage(image, charRegion.srcClip.left, charRegion.srcClip.top);
            return true;
        }
        return false;
    }

    TextureRegion TiledWindowFactory::getChar(char c) const
    {
        if ((int)c < 32 || (int)c >= 127)
        {
            return TextureRegion();
        }
        c -= 32;
        return characters.size() > c ? characters[int(c)] : TextureRegion();
    }

    bool TiledWindowFactory::addSpecialCharImage(int c, const sf::Image& image)
    {
        TextureRegion charRegion = getSpecialChar(c);
        if (charRegion.texture)
        {
            spritesheet.addImage(image, charRegion.srcClip.left, charRegion.srcClip.top);
            return true;
        }
        return false;
    }

    TextureRegion TiledWindowFactory::getSpecialChar(int c) const
    {
        if (specialCharacters.size() > c && c >= 0)
        {
            return specialCharacters[c];
        }
        return TextureRegion();
    }
    
    //////////////////// TiledWindow ////////////////////
    void TiledWindow::Cell::draw(float x, float y, sf::RenderWindow& window) const
    {
        for (auto sprite : sprites)
        {
            sprite.setPosition(x, y);
            window.draw(sprite);
        }
    }
    ////////////////////
    
    void foreach_xy(std::vector<std::vector<TiledWindow::Cell*> >& cells, int xBegin, int xEnd, int yBegin, int yEnd, std::function<void(int x, int y, TiledWindow::Cell*)> function)
    {
        for (int y = yBegin; y < yEnd; y++)
        {
            for (int x = xBegin; x < xEnd; x++)
            {
                function(x, y, cells[x][y]);
            }
        }
    }

    void foreach_yx(std::vector<std::vector<TiledWindow::Cell*> >& cells, int xBegin, int xEnd, int yBegin, int yEnd, std::function<void(int x, int y, TiledWindow::Cell*)> function)
    {
        for (int x = xBegin; x < xEnd; x++)
        {
            for (int y = yBegin; y < yEnd; y++)
            {
                function(x, y, cells[x][y]);
            }
        }
    }

    TiledWindow::TiledWindow(TiledWindowFactory& factory)
        : factory(factory), _windowSize(0, 0), windowPosition(0, 0), windowSize(_windowSize)
    {
    }

    TiledWindow::~TiledWindow()
    {
        foreach_xy(cells, 0, 0, _windowSize.x, _windowSize.y, [] (int x, int y, TiledWindow::Cell* cell) { delete cell; });
    }

    TiledWindow& TiledWindow::init(const sf::Vector2i& _windowSize, int cellSize, int imageSize)
    {
        foreach_xy(cells, 0, 0, _windowSize.x, _windowSize.y, [] (int x, int y, TiledWindow::Cell* cell) { delete cell; });
        this->_windowSize = _windowSize;
        this->cellSize = cellSize;
        this->scaling = 1.0f * cellSize / imageSize;
        for (int x = 0; x < _windowSize.x; x++)
        {
            std::vector<Cell*> innerCells;
            for (int y = 0; y < _windowSize.y; y++)
            {
                innerCells.push_back(new Cell());
            }
            cells.push_back(innerCells);
        }
        cursor.x = 0;
        cursor.y = 0;
        return *this;
    }

    const sf::Vector2i& TiledWindow::getWindowSize() const
    {
        return _windowSize;
    }
    
    sf::FloatRect TiledWindow::getRenderBound() const
    {
        return sf::FloatRect(windowPosition.x, windowPosition.y, _windowSize.x * cellSize, _windowSize.y * cellSize);
    }

    bool TiledWindow::inRange(int x, int y) const
    {
        bool temp = x >= 0 && y >= 0 && x < _windowSize.x && y < _windowSize.y;
        return temp;
    }

    bool TiledWindow::inRange(const sf::Vector2i& position) const
    {
        return inRange(position.x, position.y);
    }

    bool TiledWindow::moveCursor(int x, int y)
    {
        if (inRange(x, y))
        {
            cursor.x = x;
            cursor.y = y;
            return true;
        }
        return false;
    }

    TiledWindow& TiledWindow::advanceCursor()
    {
        cursor.x += 1;
        if (cursor.x >= _windowSize.x)
        {
            cursor.x = 0;
            cursor.y += 1;
        }
        if (cursor.y >= _windowSize.y)
        {
            cursor.y = 0;
        }
        return *this;
    }

    TiledWindow& TiledWindow::moveWindow(const sf::Vector2f& moveVec)
    {
        windowPosition += moveVec;
        return *this;
    }

    TiledWindow& TiledWindow::setWindowPosition(const sf::Vector2f& position)
    {
        windowPosition = position;
        return *this;
    }

    TiledWindow& TiledWindow::setWindowPosition(int x, int y)
    {
        windowPosition.x = x;
        windowPosition.y = y;
        return *this;
    }

    TiledWindow& TiledWindow::alignWindow(AlignmentX alignmentX, AlignmentY alignmentY, const sf::Vector2f& targetPosition, const sf::Vector2f& offset)
    {
        auto bound = getRenderBound();
        zf::alignRect(bound, alignmentX, alignmentY, targetPosition, offset);
        setWindowPosition(bound.left, bound.top);
        return *this;
    }

    TextureRegion TiledWindow::getChar(char c) const
    {
        auto region = factory.getChar(c);
        region.defaultScaleX = scaling;
        region.defaultScaleY = scaling;
        return region;
    }

    TextureRegion TiledWindow::getSpecialChar(int c) const
    {
        auto region = factory.getSpecialChar(c);
        region.defaultScaleX = scaling;
        region.defaultScaleY = scaling;
        return region;
    }
    //////////////////////////////////// TiledWindow drawing methods ////////////////////////////////////
    TiledWindow& TiledWindow::clean()
    {
        return clean(0, 0, _windowSize.x, _windowSize.y);
    }
    
    TiledWindow& TiledWindow::clean(int x, int y)
    {
        cells[x][y]->sprites.clear();
        return *this;
    }

    TiledWindow& TiledWindow::clean(const sf::Vector2i& cell)
    {
        return clean(cell.x, cell.y);
    }
    
    TiledWindow& TiledWindow::clean(int xStart, int yStart, int width, int height)
    {
        for (int x = xStart; x < xStart + width; x++)
        {
            for (int y = yStart; y < yStart + height; y++)
            {
                clean(x, y);
            }
        }
        return *this;
    }

    TiledWindow& TiledWindow::clean(const sf::IntRect& region)
    {
        return clean(region.left, region.top, region.width, region.height);
    }

    ////////////////////
    TiledWindow& TiledWindow::fill(const sf::Color& color)
    {
        return fill(0, 0, _windowSize.x, _windowSize.y, color);
    }
    
    TiledWindow& TiledWindow::fill(int x, int y, const sf::Color& color)
    {
        auto sprite = getSpecialChar(TiledWindowFactory::Fill).createSprite();
        sprite.setColor(color);
        putSprite(x, y, sprite);
        return *this;
    }

    TiledWindow& TiledWindow::fill(int xStart, int yStart, int width, int height, const sf::Color& color)
    {
        auto sprite = getSpecialChar(TiledWindowFactory::Fill).createSprite();
        sprite.setColor(color);
        for (int x = xStart; x < xStart + width; x++)
        {
            for (int y = yStart; y < yStart + height; y++)
            {
                putSprite(x, y, sprite);
            }
        }
        return *this;
    }

    TiledWindow& TiledWindow::fill(const sf::IntRect& bound, const sf::Color& color)
    {
        return fill(bound.left, bound.top, bound.width, bound.height, color);
    }
    ////////////////////


    TiledWindow& TiledWindow::draw(sf::RenderWindow& window)
    {
        for (int y = 0; y < _windowSize.y; y++)
        {
            for (int x = 0; x < _windowSize.x; x++)
            {
                cells[x][y]->draw(x * cellSize + windowPosition.x, y * cellSize + windowPosition.y, window);
            }
        }
        return *this;
    }

    //////////////////// strings ////////////////////
    TiledWindow& TiledWindow::putString(const std::string& str, const sf::Color& color)
    {
        for (int i = 0; i < str.size(); i++)
        {
            putChar(str[i], color);
        }
        return *this;
    }

    TiledWindow& TiledWindow::putString(int x, int y, const std::string& str, const sf::Color& color)
    {
        if (moveCursor(x, y))
        {
            return putString(str, color);
        }
        return *this;
    }

    TiledWindow& TiledWindow::putString(int x, int y, int width, const std::string& str, AlignmentX alignment, int offset, const sf::Color& color)
    {
        if (alignment == AlignmentX::Left)
        {
            return putString(x + offset, y, str, color);
        }
        else if (alignment == AlignmentX::Right)
        {
            return putString(x + width - str.size() - offset, y, str, color);
        }
        else if (alignment == AlignmentX::Center)
        {
            return putString(x + (width - str.size())/2 + offset, y, str, color);
        }
        else
        {
            return putString(x + offset, y, str, color);
        }
    }

    //////////////////// sprites ////////////////////
    TiledWindow& TiledWindow::putSprite(const sf::Sprite& sprite)
    {
        if (inRange(cursor))
        {
            cells[cursor.x][cursor.y]->sprites.push_back(sprite);
            advanceCursor();
        }
        return *this;
    }

    TiledWindow& TiledWindow::putSprite(int x, int y, const sf::Sprite& sprite)
    {
        if (moveCursor(x, y))
        {
            return putSprite(sprite);
        }
        return *this;
    }
    
    TiledWindow& TiledWindow::putSprite(const sf::IntRect& bound, const sf::Sprite& sprite)
    {
        return putSprite(bound.left, bound.top, bound.width, bound.height, sprite);
    }

    TiledWindow& TiledWindow::putSprite(int xStart, int yStart, int width, int height, const sf::Sprite& sprite)
    {
        for (int x = xStart; x < xStart + width; x++)
        {
            for (int y = yStart; y < yStart + height; y++)
            {
                putSprite(x, y, sprite);
            }
        }
        return *this;
    }
    //////////////////// char ////////////////////
    TiledWindow& TiledWindow::putChar(char c, const sf::Color& color)
    {
        auto sprite = getChar(c).createSprite();
        sprite.setColor(color);
        sprite.setScale(scaling, scaling);
        putSprite(sprite);
        return *this;
    }

    TiledWindow& TiledWindow::putChar(int x, int y, char c, const sf::Color& color)
    {
        if (moveCursor(x, y))
        {
            return putChar(c, color);
        }
        return *this;
    }
    //////////////////// border ////////////////////
    void TiledWindow::drawEdgeBorder(const sf::Color& color)
    {
        drawEdgeBox(sf::IntRect(0, 0, _windowSize.x, _windowSize.y), color);
    }

    void TiledWindow::drawCenterBorder(const sf::Color& color)
    {
        drawCenterBox(sf::IntRect(0, 0, _windowSize.x, _windowSize.y), color);
    }

    //////////////////// box ////////////////////
    void TiledWindow::drawEdgeBox(const sf::IntRect& bound, const sf::Color& color)
    {
        if (bound.width < 2 || bound.height < 2)
        {
            return;
        }
        putSprite(bound.left, bound.top, zf::setCopyColor(getSpecialChar(TiledWindowFactory::Border[TiledWindowFactory::NORTH_BIT | TiledWindowFactory::WEST_BIT]).createSprite(), color));
        sf::Sprite top = zf::setCopyColor(getSpecialChar(TiledWindowFactory::Border[TiledWindowFactory::NORTH_BIT]).createSprite(), color);
        for (int i = 0; i < bound.width - 2; i++)
        {
            putSprite(top);
        }
        putSprite(rightOf(bound), topOf(bound), zf::setCopyColor(getSpecialChar(TiledWindowFactory::Border[TiledWindowFactory::NORTH_BIT | TiledWindowFactory::EAST_BIT]).createSprite(), color));
        sf::Sprite left = zf::setCopyColor(getSpecialChar(TiledWindowFactory::Border[TiledWindowFactory::WEST_BIT]).createSprite(), color);
        sf::Sprite right = zf::setCopyColor(getSpecialChar(TiledWindowFactory::Border[TiledWindowFactory::EAST_BIT]).createSprite(), color);
        for (int y = 1; y < bound.height - 1; y++)
        {
            putSprite(leftOf(bound), bound.top + y, left);
            putSprite(rightOf(bound), bound.top + y, right);
        }
        putSprite(leftOf(bound), bottomOf(bound), zf::setCopyColor(getSpecialChar(TiledWindowFactory::Border[TiledWindowFactory::SOUTH_BIT | TiledWindowFactory::WEST_BIT]).createSprite(), color));
        sf::Sprite bottom = zf::setCopyColor(getSpecialChar(TiledWindowFactory::Border[TiledWindowFactory::SOUTH_BIT]).createSprite(), color);
        for (int i = 0; i < bound.width - 2; i++)
        {
            putSprite(bottom);
        }
        putSprite(rightOf(bound), bottomOf(bound), zf::setCopyColor(getSpecialChar(TiledWindowFactory::Border[TiledWindowFactory::SOUTH_BIT | TiledWindowFactory::EAST_BIT]).createSprite(), color));
    }

    void TiledWindow::drawCenterBox(const sf::IntRect& bound, const sf::Color& color)
    {
        if (bound.width < 2 || bound.height < 2)
        {
            return;
        }
        putSprite(leftOf(bound), topOf(bound), zf::setCopyColor(getSpecialChar(TiledWindowFactory::Cross[TiledWindowFactory::SOUTH_BIT | TiledWindowFactory::EAST_BIT]).createSprite(), color));
        sf::Sprite horizontal = zf::setCopyColor(getSpecialChar(TiledWindowFactory::Cross[TiledWindowFactory::EAST_BIT | TiledWindowFactory::WEST_BIT]).createSprite(), color);
        for (int i = 0; i < bound.width - 2; i++)
        {
            putSprite(horizontal);
        }
        putSprite(rightOf(bound), topOf(bound), zf::setCopyColor(getSpecialChar(TiledWindowFactory::Cross[TiledWindowFactory::SOUTH_BIT | TiledWindowFactory::WEST_BIT]).createSprite(), color));
        sf::Sprite vertical = zf::setCopyColor(getSpecialChar(TiledWindowFactory::Cross[TiledWindowFactory::NORTH_BIT|TiledWindowFactory::SOUTH_BIT]).createSprite(), color);
        for (int y = 1; y < bound.height - 1; y++)
        {
            putSprite(leftOf(bound), bound.top + y, vertical);
            putSprite(rightOf(bound), bound.top + y, vertical);
        }
        putSprite(leftOf(bound), bottomOf(bound), zf::setCopyColor(getSpecialChar(TiledWindowFactory::Cross[TiledWindowFactory::NORTH_BIT | TiledWindowFactory::EAST_BIT]).createSprite(), color));
        for (int i = 0; i < bound.width - 2; i++)
        {
            putSprite(horizontal);
        }
        putSprite(rightOf(bound), bottomOf(bound), zf::setCopyColor(getSpecialChar(TiledWindowFactory::Cross[TiledWindowFactory::NORTH_BIT | TiledWindowFactory::WEST_BIT]).createSprite(), color));
    }
}
