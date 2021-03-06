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
#include "zf_term.hpp"
#include <iostream>
namespace zf
{
    //////////////////// special characters ////////////////////
    /**
     * The bit here mirrors that of zf_direction
     */
    const int NORTH_BIT = 1;
    const int EAST_BIT = 2;
    const int SOUTH_BIT = 4;
    const int WEST_BIT = 8;
    const int Border[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    const int Cross[16] = {16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
    const int Center_dot = 32;
    const int Alternate[2] = { 33, 34 };
    const int Up = 0;
    const int Right = 1;
    const int Down = 2;
    const int Left = 3;
    const int Arrow[4] = { 35, 36 , 37, 38 };
    const int Fill = 39;
    const int TotalSpecialChar = Fill + 1;
    const int TotalRequired = 127 - 32 + TotalSpecialChar;

    //////////////////// TermCell ////////////////////
    TermCell::TermCell(const sf::Sprite& fg, const sf::Sprite& bg)
        : foreground(fg), background(bg)
    {
    }
    
    //////////////////// TermWindow ////////////////////
    TermWindow::TermWindow(Terminal& screen)
        : screen(screen), cursor(0, 0), visible(true)
    {
    }

    TermWindow::~TermWindow()
    {
    }

    const sf::IntRect& TermWindow::getBound() const
    {
        return bound;
    }

    TermWindow& TermWindow::resize(const sf::IntRect& b)
    {
        bound = screen.resize(b);
        cells.clear();
        for (int x = 0; x < bound.width; x++)
        {
            std::vector<TermCell> innerCells;
            for (int y = 0; y < bound.height; y++)
            {
                innerCells.push_back(TermCell());
            }
            cells.push_back(innerCells);
        }
        cursor.x = bound.left;
        cursor.y = bound.top;
        return *this;
    }

    TermWindow& TermWindow::resize(int x, int y, int width, int height)
    {
        return resize(sf::IntRect(x, y, width, height));
    }

    bool TermWindow::inRange(int x, int y) const
    {
        return x >= 0 && y >= 0 && x < bound.width && y < bound.height;
    }

    bool TermWindow::inRange(const sf::Vector2i& position) const
    {
        return inRange(position.x, position.y);
    }

    bool TermWindow::moveCursor(int x, int y)
    {
        if (inRange(x, y))
        {
            cursor.x = x;
            cursor.y = y;
            return true;
        }
        return false;
    }

    void TermWindow::putSprite_f(const sf::Sprite& sprite)
    {
        if (inRange(cursor))
        {
            cells[cursor.x][cursor.y].foreground = sprite;
            advanceCursor();
        }
    }
    
    void TermWindow::putSprite_b(const sf::Sprite& sprite)
    {
        if (inRange(cursor))
        {
            cells[cursor.x][cursor.y].background = sprite;
            advanceCursor();
        }
    }

    void TermWindow::putSprite_fb(const sf::Sprite& fg, const sf::Sprite& bg)
    {
        if (inRange(cursor))
        {
            cells[cursor.x][cursor.y].foreground = fg;
            cells[cursor.x][cursor.y].background = bg;
            advanceCursor();
        }
    }

    void TermWindow::putSprite_xyf(int x, int y, const sf::Sprite& sprite)
    {
        if (moveCursor(x, y))
        {
            putSprite_f(sprite);
        }
    }

    void TermWindow::putSprite_xyb(int x, int y, const sf::Sprite& sprite)
    {
        if (moveCursor(x, y))
        {
            putSprite_b(sprite);
        }
    }

    void TermWindow::putSprite_xyfb(int x, int y, const sf::Sprite& fg, const sf::Sprite& bg)
    {
        if (moveCursor(x, y))
        {
            putSprite_fb(fg, bg);
        }
    }

    void TermWindow::putString(const std::string& str, const sf::Color& color)
    {
        for (int i = 0; i < str.size(); i++)
        {
            auto sprite = screen.getChar(str[i]).createSprite();
            sprite.setColor(color);
            putSprite_f(sprite);
        }
    }

    void TermWindow::putString_xy(int x, int y, const std::string& str, const sf::Color& color)
    {
        if (moveCursor(x, y))
        {
            putString(str, color);
        }
    }
    
    void TermWindow::putString_row(int x, int y, int width, TermWindow::TextAlignmentX alignment, int offset, const std::string& message, const sf::Color& color)
    {
        if (alignment == TextAlignmentX::Left)
        {
            putString_xy(x + offset, y, message, color);
        }
        else if (alignment == TextAlignmentX::Right)
        {
            putString_xy(x + width - message.size() - offset, y, message, color);
        }
        else 
        {
            putString_xy(x + (width - message.size())/2 + offset, y, message, color);
        }
    }

    void TermWindow::putChar(char c, const sf::Color& color)
    {
        auto sprite = screen.getChar(c).createSprite();
        sprite.setColor(color);
        putSprite_f(sprite);
    }

    void TermWindow::putChar_xy(int x, int y, char c, const sf::Color& color)
    {
        if (moveCursor(x, y))
        {
            putChar(c, color);
        }
    }

    const bool& TermWindow::isVisible() const
    {
        return visible;
    }

    void TermWindow::drawEdgeBorder(const sf::Color& color)
    {
        drawEdgeBox(sf::IntRect(0, 0, bound.width, bound.height), color);
    }

    void TermWindow::drawCenterBorder(const sf::Color& color)
    {
        drawCenterBox(sf::IntRect(0, 0, bound.width, bound.height), color);
    }

    void TermWindow::drawEdgeBox(const sf::IntRect& boxBound, const sf::Color& color)
    {
        if (boxBound.width < 2 || boxBound.height < 2)
        {
            return;
        }
        putSprite_xyf(boxBound.left, boxBound.top, zf::setCopyColor(screen.getSpecialChar(Border[NORTH_BIT | WEST_BIT]).createSprite(), color));
        sf::Sprite top = zf::setCopyColor(screen.getSpecialChar(Border[NORTH_BIT]).createSprite(), color);
        for (int i = 0; i < boxBound.width - 2; i++)
        {
            putSprite_f(top);
        }
        putSprite_xyf(rightOf(boxBound), topOf(boxBound), zf::setCopyColor(screen.getSpecialChar(Border[NORTH_BIT | EAST_BIT]).createSprite(), color));
        sf::Sprite left = zf::setCopyColor(screen.getSpecialChar(Border[WEST_BIT]).createSprite(), color);
        sf::Sprite right = zf::setCopyColor(screen.getSpecialChar(Border[EAST_BIT]).createSprite(), color);
        for (int y = 1; y < boxBound.height - 1; y++)
        {
            putSprite_xyf(leftOf(boxBound), boxBound.top + y, left);
            putSprite_xyf(rightOf(boxBound), boxBound.top + y, right);
        }
        putSprite_xyf(leftOf(boxBound), bottomOf(boxBound), zf::setCopyColor(screen.getSpecialChar(Border[SOUTH_BIT | WEST_BIT]).createSprite(), color));
        sf::Sprite bottom = zf::setCopyColor(screen.getSpecialChar(Border[SOUTH_BIT]).createSprite(), color);
        for (int i = 0; i < boxBound.width - 2; i++)
        {
            putSprite_f(bottom);
        }
        putSprite_xyf(rightOf(boxBound), bottomOf(boxBound), zf::setCopyColor(screen.getSpecialChar(Border[SOUTH_BIT | EAST_BIT]).createSprite(), color));
    }

    void TermWindow::drawCenterBox(const sf::IntRect& boxBound, const sf::Color& color)
    {
        if (boxBound.width < 2 || boxBound.height < 2)
        {
            return;
        }
        putSprite_xyf(leftOf(boxBound), topOf(boxBound), zf::setCopyColor(screen.getSpecialChar(Cross[SOUTH_BIT | EAST_BIT]).createSprite(), color));
        sf::Sprite horizontal = zf::setCopyColor(screen.getSpecialChar(Cross[EAST_BIT | WEST_BIT]).createSprite(), color);
        for (int i = 0; i < boxBound.width - 2; i++)
        {
            putSprite_f(horizontal);
        }
        putSprite_xyf(rightOf(boxBound), topOf(boxBound), zf::setCopyColor(screen.getSpecialChar(Cross[SOUTH_BIT | WEST_BIT]).createSprite(), color));
        sf::Sprite vertical = zf::setCopyColor(screen.getSpecialChar(Cross[NORTH_BIT|SOUTH_BIT]).createSprite(), color);
        for (int y = 1; y < boxBound.height - 1; y++)
        {
            putSprite_xyf(leftOf(boxBound), boxBound.top + y, vertical);
            putSprite_xyf(rightOf(boxBound), boxBound.top + y, vertical);
        }
        putSprite_xyf(leftOf(boxBound), bottomOf(boxBound), zf::setCopyColor(screen.getSpecialChar(Cross[NORTH_BIT | EAST_BIT]).createSprite(), color));
        for (int i = 0; i < boxBound.width - 2; i++)
        {
            putSprite_f(horizontal);
        }
        putSprite_xyf(rightOf(boxBound), bottomOf(boxBound), zf::setCopyColor(screen.getSpecialChar(Cross[NORTH_BIT | WEST_BIT]).createSprite(), color));
    }

    void TermWindow::clear(const sf::Color& clearColor)
    {
        clear_r(sf::IntRect(0, 0, bound.width, bound.height), clearColor);
    }

    void TermWindow::clear_r(sf::IntRect region, const sf::Color& color)
    {
        region = zf::fitRectByShrinking(region, sf::IntRect(0, 0, bound.width, bound.height));
        sf::Sprite fill = screen.getSpecialChar(Fill).createSprite();
        fill.setColor(color);
        for (int x = 0; x < region.width; x++)
        {
            for (int y = 0; y < region.height; y++)
            {
                cells[x][y].foreground = sf::Sprite();
                cells[x][y].background = fill;
            }
        }
    }

    void TermWindow::empty()
    {
        empty_r(sf::IntRect(0, 0, bound.width, bound.height));
    }

    void TermWindow::empty_r(sf::IntRect region)
    {
        region = zf::fitRectByShrinking(region, sf::IntRect(0, 0, bound.width, bound.height));
        for (int x = 0; x < region.width; x++)
        {
            for (int y = 0; y < region.height; y++)
            {
                cells[x][y].foreground = sf::Sprite();
                cells[x][y].background = sf::Sprite();
            }
        }
    }

    void TermWindow::setVisible(bool visibility)
    {
        this->visible = visibility;
    }

    void TermWindow::bringToFront()
    {
        screen.bringToFront(*this);
    }

    void TermWindow::updateScreen(bool putMode) 
    {
        if (putMode)
        {
            for (int x = 0; x < bound.width; x++)
            {
                for (int y = 0; y < bound.height; y++)
                {
                    screen.directPut(cells[x][y], x + bound.left, y + bound.top);
                }
            }
        }
        else
        {
            for (int x = 0; x < bound.width; x++)
            {
                for (int y = 0; y < bound.height; y++)
                {
                    screen.directDraw(cells[x][y], x + bound.left, y + bound.top);
                }
            }
        }
    }

    void TermWindow::advanceCursor()
    {
        cursor.x += 1;
        if (cursor.x >= bound.width)
        {
            cursor.x = 0;
            cursor.y += 1;
        }
        if (cursor.y >= bound.height)
        {
            cursor.y = 0;
        }
    }

    //////////////////// Terminal ////////////////////
    Terminal::Terminal(sf::RenderWindow& window, const sf::Vector2i& termSize)
        : renderWindow(window), termBound(0, 0, termSize.x, termSize.y)
        , charTexture(nullptr), inited(false)
    {
        cells.clear();
        for (int x = 0; x < termSize.x; x++) 
        {
            std::vector<TermCell> innerCells;
            for (int y = 0; y < termSize.y; y++) 
            {
                innerCells.push_back(TermCell());
            }
            cells.push_back(innerCells);
        }
    }

    Terminal::~Terminal()
    {
        for (auto window : windows)
        {
            delete window;
        }
        if (charTexture)
        {
            delete charTexture;
        }
    }

    void Terminal::init(const sf::Vector2i& cellSize, const sf::Vector2i& spriteSize, const int maxRow, const int maxCol)
    {
        if (inited)
        {
            return;
        }
        inited = true;
        this->cellSize = cellSize;
        ascii_starts = 0;
        ascii_ends = ascii_starts;

        float scale = cellSize.x * 1.0f / spriteSize.x;
        const sf::Vector2i spritesheetSize(spriteSize.x * maxCol, spriteSize.y * maxRow);
        {
            charTexture = new sf::Texture();
            charTexture->create(spritesheetSize.x, spritesheetSize.y);
            charSpriteSheet.create(charTexture, sf::IntRect(0, 0, spritesheetSize.x, spritesheetSize.y));
            int row = 0, col = 0;
            for (int i = 32; i < 127; i++)
            {
                auto region = charSpriteSheet.createRegion(sf::IntRect(col * spriteSize.x, row * spriteSize.y, spriteSize.x, spriteSize.y));
                region.defaultScaleX = scale;
                region.defaultScaleY = scale;
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
                auto region = charSpriteSheet.createRegion(sf::IntRect(col * spriteSize.x, row * spriteSize.y, spriteSize.x, spriteSize.y));
                region.defaultScaleX = scale;
                region.defaultScaleY = scale;
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
                auto region = charSpriteSheet.createRegion(sf::IntRect(col * spriteSize.x, row * spriteSize.y, spriteSize.x, spriteSize.y));
                region.defaultScaleX = scale;
                region.defaultScaleY = scale;
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

    const sf::IntRect& Terminal::getTermBound() const
    {
        return termBound;
    }

    const sf::Vector2i& Terminal::getCellSize() const
    {
        return cellSize;
    }

    bool Terminal::inRange(int x, int y) const
    {
        return termBound.contains(x, y);
    }

    void Terminal::updateRenderWindow(bool singleDraw)
    {
        for (auto window : windows)
        {
            if (window->isVisible())
            {
                window->updateScreen(singleDraw);
            }
        }
        if (singleDraw)
        {
            /**
             * We always assume that the sprites are already in the correct position.
             */
            for (int x = 0; x < termBound.width; x++)
            {
                for (int y = 0; y < termBound.height; y++)
                {
                    renderWindow.draw(cells[x][y].background);
                    renderWindow.draw(cells[x][y].foreground);
                }
            }
        }
    }

    sf::IntRect Terminal::resize(const sf::IntRect& rect) const
    {
        sf::IntRect r = rect;
        return fitRectByShrinking(r, termBound);
    }
    
    void Terminal::freeWindow(TermWindow& window)
    {
        auto result = std::find(windows.begin(), windows.end(), &window);
        if (result != windows.end())
        {
            windows.erase(result);
        }
        delete &window;
    }

    TermWindow* Terminal::newWindow(const sf::IntRect& bound)
    {
        return newWindow(bound.left, bound.top, bound.width, bound.height);
    }

    TermWindow* Terminal::newWindow(int x, int y, int width, int height)
    {
        TermWindow* window = new TermWindow(*this);
        window->resize(x, y, width, height);
        windows.push_back(window);
        return window;
    }

    void Terminal::directPut(const TermCell& cell, int x, int y)
    {
        if (inRange(x, y))
        {
            cells[x][y].foreground = cell.foreground;
            cells[x][y].background = cell.background;
            cells[x][y].foreground.setPosition(x * cellSize.x, y * cellSize.y);
            cells[x][y].background.setPosition(x * cellSize.y, y * cellSize.y);
        }
    }

    void Terminal::directDraw(TermCell& cell, int x, int y)
    {
        if (inRange(x, y))
        {
            cell.foreground.setPosition(x * cellSize.x, y * cellSize.y);
            cell.background.setPosition(x * cellSize.y, y * cellSize.y);
            renderWindow.draw(cell.background);
            renderWindow.draw(cell.foreground);
        }
    }

    void Terminal::autoLoad(const std::string& path)
    {
        if (!charTexture)
        {
            return;
        }
        sf::Image image;

        /// basic ascii character
        for (int i = 32; i < 127; i++)
        {
            image.loadFromFile(path + "/basic/" + intToString(i) + ".png");
            if (!addCharImage(i, image))
            {
                std::cout << "-- Fail to add char " << char(i) << std::endl;
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
                std::cout << "-- Fail to add char " << char(i) << std::endl;
            }
        } 
    }

    bool Terminal::addCharImage(char c, const sf::Image& image)
    {
        TextureRegion charRegion = getChar(c);
        if (charRegion.texture)
        {
            charSpriteSheet.addImage(image, charRegion.srcClip.left, charRegion.srcClip.top);
            return true;
        }
        return false;
    }
    
    TextureRegion Terminal::getChar(char c) const
    {
        if ((int)c < 32 || (int)c >= 127)
        {
            return emptyRegion;
        }
        c -= 32;
        return characters.size() > c ? characters[int(c)] : emptyRegion;
    }

    bool Terminal::addSpecialCharImage(int c, const sf::Image& image)
    {
        TextureRegion charRegion = getSpecialChar(c);
        if (charRegion.texture)
        {
            charSpriteSheet.addImage(image, charRegion.srcClip.left, charRegion.srcClip.top);
            return true;
        }
        return false;
    }

    TextureRegion Terminal::getSpecialChar(int c) const
    {
        if (specialCharacters.size() > c && c >= 0)
        {
            return specialCharacters[c];
        }
        return emptyRegion;
    }

    void Terminal::bringToFront(TermWindow& window)
    {
        for (auto it = windows.begin(); it != windows.end();)
        {
            if (*it == &window)
            {
                it = windows.erase(it);
                windows.push_back(&window);
                break;
            }
            it++;
        }
    }
}

