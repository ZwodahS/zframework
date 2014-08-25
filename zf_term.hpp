/*
 *           DO WHAT THE F*** YOU WANT TO PUBLIC LICENSE
 *                   Version 2, December 2004
 *
 * Copyright (C) 2013- ZwodahS(ericnjf@gmail.com)
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
 */
#ifndef _ZFRAMEWORK_ZF_TERM_HPP
#define _ZFRAMEWORK_ZF_TERM_HPP
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
/***
 * zf_term dependency :
 *      .1 zf_spritesheet.hpp
 *      .2 zf_rect.hpp
 *      .3 zf_sprite.hpp
 *      .4 zf_conversion.hpp
 */
#include "zf_spritesheet.hpp"
#include "zf_rect.hpp"
#include "zf_sprite.hpp"
#include "zf_conversion.hpp"
namespace zf
{
    //////////////////// special characters are used in term screen ////////////////////
    extern const int NORTH_BIT, EAST_BIT, SOUTH_BIT, WEST_BIT;
    extern const int Up, Right, Down, Left;
    extern const int Border[16];
    extern const int Cross[16];
    extern const int Center_dot;
    extern const int Diagonal[2];
    extern const int Alternate[2];
    extern const int Arrow[4];
    extern const int Fill;
    extern const int TotalSpecialChar;

    //////////////////// TermCell ////////////////////
    /**
     * A single cell in the terminal.
     * There are a few things that can be displayed and customized.
     * User of zf_term should not use TermCell directly.
     */
    struct TermCell
    {
        /**
         * TODO For now we will use sprite. Might change to render states and texture stuffs later.
         */
        sf::Sprite foreground;
        sf::Sprite background;
        TermCell(const sf::Sprite& foreground = sf::Sprite(), const sf::Sprite& background = sf::Sprite());
    };
    class Terminal;
    //////////////////// TermWindow ////////////////////
    class TermWindow
    {
    public:
        enum class TextAlignmentX
        {
            Left,
            Center,
            Right,
        };
        ~TermWindow();
    private:
        /**
         * private constructor, do not create directly.
         * use new window method in term screen.
         */
        TermWindow(Terminal& screen); 
        friend Terminal; 
        //////////////////// utility methods ////////////////////
    public:
        const bool& isVisible() const;
       /**
        * Get bound returns the bound of this window within the screen.
        * however, drawing always starts from 0.
        *
        * ALL position used by termWindow methods are relative to itself.
        * It wouldn't make sense if you still need to care about the position of this window relative to the screen.
        */ 
        const sf::IntRect& getBound() const;
        /**
         * Resize will attempt to resize to the size you want.
         * But if it is out of bound it will fit itself into the bound.
         *
         * To make it easier, upon resizing, all cells data are cleared.
         */
        TermWindow& resize(const sf::IntRect& bound);
        TermWindow& resize(int x, int y, int width, int height);
        
        bool inRange(int x, int y) const;
        bool inRange(const sf::Vector2i& position) const;
        /**
         * move the cursor to this position.
         * Return false if not able to move there (out of bound)
         */
        bool moveCursor(int x, int y);
        /**
         * clear the window by flooding the window with a single color.
         */
        void clear(const sf::Color& color = sf::Color(0, 0, 0, 255));
        void clear_r(sf::IntRect region, const sf::Color& color = sf::Color(0, 0, 0, 255));

        void empty();
        void empty_r(sf::IntRect region);


        void setVisible(bool visibility);
        void bringToFront();
        //////////////////// Put Sprite methods ////////////////////
    public:
        /**
         * Put Sprite at foreground(f suffix), background(b suffix), or both(fg suffix)
         * various argument range.
         */
        void putSprite_f(const sf::Sprite& sprite);
        void putSprite_b(const sf::Sprite& sprite);
        void putSprite_fb(const sf::Sprite& fg, const sf::Sprite& bg);
        /**
         * move the cursor to the xy position and put
         * if the position specified is out of range. Nothing is done.
         */
        void putSprite_xyf(int x, int y, const sf::Sprite& sprite);
        void putSprite_xyb(int x, int y, const sf::Sprite& sprite);
        void putSprite_xyfb(int x, int y, const sf::Sprite& fg, const sf::Sprite& bg);
        //////////////////// Put String methods ////////////////////
    public:
        /**
         * Put a string onto the screen. It is always placed at the foreground.
         */
        void putString(const std::string& str, const sf::Color& color = sf::Color(255, 255, 255, 255));
        void putString_xy(int x, int y, const std::string& str, const sf::Color& color = sf::Color(255, 255, 255, 255));
        void putString_row(int x, int y, int width, TextAlignmentX alignment, int offset, const std::string& message, const sf::Color& color = sf::Color(255, 255, 255, 255));


        //////////////////// Put a single char /////////////////////
    public:
        void putChar(char c, const sf::Color& color = sf::Color(255, 255, 255, 255));
        void putChar_xy(int x, int y, char c, const sf::Color& color = sf::Color(255, 255, 255, 255));
        
        //////////////////// Border methods ////////////////////
    public:
        /**
         * Draw border, edge border exist at the edge of the last tiles, while center border is in the middle of the tiles.
         * Just try it ..
         */
        void drawEdgeBorder(const sf::Color& color = sf::Color::White);
        void drawCenterBorder(const sf::Color& color = sf::Color::White);
        void drawEdgeBox(const sf::IntRect& bound, const sf::Color& color = sf::Color::White);
        void drawCenterBox(const sf::IntRect& bound, const sf::Color& color = sf::Color::White);
    private:
        /**
         * if put mode is true, then only one single cell (one single foreground and one single background) is drawn.
         * if put mode is false, then all sprites will be drawn, and their transparency will take effect.
         */
        void updateScreen(bool putMode);
        void directDraw(sf::RenderWindow& window);
        Terminal& screen;
        sf::IntRect bound;
        /**
         * Following the convention of ncurses in a way.
         */
        sf::Vector2i cursor;
        bool visible;
        std::vector<std::vector<TermCell> > cells;

        /**
         * advance cursor by 1
         */
        void advanceCursor();
    };
    //////////////////// Terminal ////////////////////
    /**
     * The core screen.
     */
    class Terminal
    {
    public:
        const TextureRegion emptyRegion = TextureRegion();
        /** 
         * window defines the window that is used.
         * termSize defines the number of rows and columns
         */
        Terminal(sf::RenderWindow& window, const sf::Vector2i& termSize);
        ~Terminal();

        /**
         * Init method must be called. 
         * This set up all the required parameters.
         *
         * cellSize is the size of each "character"
         * sprite
         *
         * There is a limit on how big the cellsize can be. 
         * Main limit the size possible for the charSpriteSheet
         * 
         * It is better if spritesize is a power of 2.
         * It is better if cellSize is a multiple of 2. (in theory)
         *
         * For example, you can provide a spritesize of 32x32 (like in the example)
         * Then if cellSize is a multiple of 2, you could get a good scaling factor
         *
         * cellSize 8 : 8/32 = 0.25
         * cellSize 16 : 16/32 = 0.5
         * cellSize 24 : 24/32 = 0.75
         * 
         * Assumption : square cell
         */
        void init(const sf::Vector2i& cellSize, const sf::Vector2i& spriteSize, const int maxRow = 20, const int maxCol = 20);
        
        /**
         * Get the term bound 
         */
        const sf::IntRect& getTermBound() const;
        /**
         * Get the size of each cell in term.
         */
        const sf::Vector2i& getCellSize() const;
        bool inRange(int x, int y) const;

        /**
         * Draw what we have onto the render window.
         * if single draw is true, only one cell will be draw.
         * If single draw if false, then each window will draw onto the render window directly,
         * in the order that they in.
         */
        void updateRenderWindow(bool singleDraw = true);

        /**
         * Create a new window in this region.
         * If the window is out of bound, it will automatically resize itself to fit in.
         */
        TermWindow* newWindow(const sf::IntRect& bound);
        TermWindow* newWindow(int x, int y, int width, int height);

        /**
         * Resize this rect to fit into this bound.
         */
        sf::IntRect resize(const sf::IntRect& rect) const;
        /**
         * Free this window.
         */
        void freeWindow(TermWindow& window);


        /**
         * Pass in the path to the root directory of the root location of the fonts.
         * This will auto load the files.
         * The files will be
         *  root
         *  |_ basic : contains all the ascii characters, filename should be 32.png to 126.png
         *  |_ special : contains the special required characters, filename should be
         *     |_ border_0.png to border_15.png
         *     |_ cross_0.png to cross_0.png
         *     |_ center_dot.png
         *     |_ diagonal_1.png to diagonal_2.png
         *     |_ alternate_1.png to alternate_2.png
         *     |_ fill.png
         *
         * Change this if you need.
         */
        void autoLoad(const std::string& path);
        /**
         * Add a char image to the sprite sheet.
         * Only add range from 32 to 126(inclusive)
         * Return false if not in range.
         */
        bool addCharImage(char c, const sf::Image& image);
        TextureRegion getChar(char c) const;

        bool addSpecialCharImage(int c, const sf::Image& image);
        /** 
         * return -1 if fail
         */
        TextureRegion getSpecialChar(int c) const;

        void bringToFront(TermWindow& window);

        ///////////////////////////////////////////////////////////////////////
    private:
        /**
         * directly put this cell into this position.
         */
        void directPut(const TermCell& cell, int x, int y);
        void directDraw(TermCell& cell, int x, int y);
        /**
         * Pass in when update? 
         */
        sf::RenderWindow& renderWindow;
        const sf::IntRect termBound;
        /**
         * Main char sheet for the basic ascii character
         * This stores only char from 32 to 126(inclusive)
         */
        sf::Texture* charTexture;
        SpriteSheet charSpriteSheet;
        int ascii_starts;
        int ascii_ends;
        int special_starts;
        int special_ends;
        /**
         * Store char 32 to 126, index-0, so 32 is stored in position 0.
         */
        std::vector<TextureRegion> characters;
        /**
         * Store the region for the extended chars.
         */
        std::vector<TextureRegion> specialCharacters;
        /**
         * The size of each cell.
         */
        sf::Vector2i cellSize;
        /**
         * The current list of window.
         * Things will be drawn from index 0, and windows.back() will be the window at the top.
         */
        std::vector<TermWindow*> windows;
        std::vector<std::vector<TermCell> > cells;

        bool inited;
        friend TermWindow;
    };

};
#endif
