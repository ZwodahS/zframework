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
 *
 *  visit http://github.com/ZwodahS/zframework for the latest version
 */
#ifndef _ZFRAMEWORK_ZF_TWINDOW_HPP_
#define _ZFRAMEWORK_ZF_TWINDOW_HPP_
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include <vector>
/***
 * zf_twindow dependency :
 *      .1 zf_spritesheet.hpp
 *      .2 zf_rect.hpp
 *      .3 zf_sprite.hpp
 *      .4 zf_conversion.hpp
 *      .5 zf_alignment.hpp
 */
#include "zf_spritesheet.hpp"
#include "zf_rect.hpp"
#include "zf_sprite.hpp"
#include "zf_conversion.hpp"
/**
 * twindow is fork of zf_term. Instead of having a terminal, twindow will focus on drawing directly 
 * onto the renderwindow. The main purpose of twindow is the same as zf_term, providing a curse-like 
 * library on sfml.
 *
 * zf_term map closer to ncurses implementation, while twindow just provide a way to draw tiled sprites,
 * and provide ways to draw strings onto the screen.
 *
 * unlike zf_term, twindow will NOT provide the naming convention like curses.
 *  
 * Alot of things is also changed in twindow. there will be no concept of foreground and background,
 * as least not internally.
 *
 * Also, don't use it with zf_term.hpp
 */
namespace zf
{
    class TiledWindow;
    /**
     * The factory used to create all the windows.
     *
     * TiledWindowFactory holds all the assets for all the windows.
     */ 
    class TiledWindowFactory
    {
    public:
        //////////////////// int values for special characters ////////////////////
        static const int NorthBit, EastBit, SouthBit, WestBit;
        static const int Up, Right, Down, Left;
        static const int Border[16];
        static const int Cross[16];
        static const int CenterDot;
        static const int Diagonal[2];
        static const int Alternate[2];
        static const int Arrow[4];
        static const int Fill;
        static const int TotalSpecialChar;
        static const int TotalRequired;
    public: 
        TiledWindowFactory();
        ~TiledWindowFactory();

        /**
         * Init the factory.
         *
         * Assume square images,
         * maxRow and maxCol the number of col/row for the spritesheet.
         */
        void init(int imageSize, int maxRow = 20, int maxCol = 20);

        /**
         * Create a tile window with the specific values.
         *      _windowSize : the number of cells (x, and y) in the window
         *      cellSize : the size of each size.
         *
         *      cellSize should be multiple of 4s
         *      [4, 8, 12, 16, 20, 24, 28, 32]
         *      you can experiment with other values and see how it looks.
         *      
         *      The scale of the image depends on the cellSize and the image Size.
         *      Using the default image size,
         *      4 = 0.125
         *      8 = 0.25
         *      12 = 0.375
         *      16 = 0.5
         *      20 = 0.625
         *      24 = 0.75
         *      28 = 0.875
         *      32 = 1
         */
        TiledWindow* newWindow(const sf::Vector2i& _windowSize, int cellSize);

        void freeWindow(TiledWindow* window);
        
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
         */
        std::vector<std::string> autoload(const std::string& path);
        
        /**
         * Override the char image for this specific character.
         * You shouldn't call this directly, instead replace the image 
         * in the folder and let autoload takes care of it.
         */ 
        bool overrideCharImage(char c, const sf::Image& image);
        TextureRegion getChar(char c) const;
    
        /**
         * c value less than TotalSpecialChar will override the default
         * images. If adding new images, use c value starting from TotalSpecialChar
         *
         * As usual, don't override the default sprite here, replace
         * the file in the image folder.
         */
        bool addSpecialCharImage(int c, const sf::Image& image);
        TextureRegion getSpecialChar(int c) const;
        
    ////////////////////////////////////////////////////////////////////
    private:
        sf::Texture* texture;
        SpriteSheet spritesheet;

        int ascii_starts;
        int ascii_ends;
        int special_starts;
        int special_ends;
        /*
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
        int imageSize;
        /**
         * The current list of window created by this TiledWindowFactory
         */
        std::vector<TiledWindow*> windows;

        bool inited;
        friend TiledWindow;
    };

    class TiledWindow
    {
    //////////////////// Internally used objects ////////////////////
    public:
        struct Cell
        {
            std::vector<sf::Sprite> sprites;
            void draw(float x, float y, sf::RenderWindow& window) const;
        };
    //////////////////// Init ////////////////////
    public:
        /**
         * Deconstructor
         */
        ~TiledWindow();
    private:
        /**
         * Constructor(private)
         * Do not create this directory, use TiledWindowFactory to create.
         */
        TiledWindow(TiledWindowFactory& factory);
        /**
         * Init the window.
         * @param the size of the window, or the number of cells in the window.
         * @param the cellsize of this window.
         * @param the image size of the factory
         */
        TiledWindow& init(const sf::Vector2i& _windowSize, int cellSize, int imageSize);
        TiledWindow& create();
        /**
         * Factory reference.
         */
        TiledWindowFactory& factory;
        friend TiledWindowFactory;
    //////////////////// Properties ////////////////////
    public:
        /**
         * Get the visibility state of the window.
         * @return true if visible, false otherwise.
         */
        const bool& isVisible() const;
        /**
         * Get the number of cells in the window.
         * @return sf::Vector2i, number of columns in the x value, number of rows in the y value.
         */
        const sf::Vector2i& getWindowSize() const;
        sf::FloatRect getRenderBound() const;
        /**
         * Check if this position is in range of the window.
         * @return true if the position is in the window.
         */
        bool inRange(int x, int y) const;
        bool inRange(const sf::Vector2i& position) const;
        /**
         * Move the window by a certain vector.
         */
        TiledWindow& moveWindow(const sf::Vector2f& moveVec);
        TiledWindow& setWindowPosition(const sf::Vector2f& position);
        TiledWindow& setWindowPosition(int x, int y);

        TiledWindow& alignWindow(AlignmentX alignmentX, AlignmentY alignmentY, const sf::Vector2f& targetPosition, const sf::Vector2f& offset = sf::Vector2f(0, 0));
        /**
         * Get the texture region representing this character, and scale it properly for this window.
         * Scaling done using the scaling version in window.
         */
        TextureRegion getChar(char c) const;
        /**
         * Get the texture region representing this special char, and scale it properly for this window.
         * Scaling done using the scaling version in window.
         */
        TextureRegion getSpecialChar(int c) const;

        const sf::Vector2i& windowSize;
    private:
        /**
         * Move the cursor to the position
         * @return true if the position is valid, else false.
         */
        bool moveCursor(int x, int y);
        /**
         * Advance the cursor by 1.
         * automatically wrap if necessary
         */
        TiledWindow& advanceCursor();
        /**
         * The cells container.
         */
        std::vector<std::vector<Cell*> > cells;
        /**
         * The cell size of the cell.
         */
        int cellSize;
        /**
         * The scaling factor of the cell.
         */
        float scaling;
        /**
         * The number of cells in the window.
         */
        sf::Vector2i _windowSize;
        /**
         * The window position
         */
        sf::Vector2f windowPosition;
        /**
         * Current cursor position.
         */
        sf::Vector2i cursor;
        /**
         * Visibility of the window
         */
        bool visible;
    //////////////////// Draw methods ////////////////////
    public:    
        /**
         * Clear all sprites in the window.
         */
        TiledWindow& clean();
        TiledWindow& clean(int x, int y);
        TiledWindow& clean(const sf::Vector2i& cell);
        TiledWindow& clean(int x, int y, int width, int height);
        TiledWindow& clean(const sf::IntRect& region);
        /**
         * Filling cells with a color
         */
        TiledWindow& fill(const sf::Color& color = sf::Color(20, 20, 20));
        TiledWindow& fill(int x, int y, const sf::Color& color = sf::Color(20, 20, 20));
        TiledWindow& fill(const sf::Vector2i& cell, const sf::Color& color = sf::Color(20, 20, 20));
        TiledWindow& fill(int x, int y, int width, int height, const sf::Color& color = sf::Color(20, 20, 20));
        TiledWindow& fill(const sf::IntRect& bound, const sf::Color& color = sf::Color(20, 20, 20));
        /**
         * Draw all stuffs onto the renderwindow.
         */ 
        TiledWindow& draw(sf::RenderWindow& window);
        //////////////////// String drawing
        TiledWindow& putString(const std::string& str, const sf::Color& color = sf::Color::White);
        TiledWindow& putString(const std::string& str, int x, int y, const sf::Color& color = sf::Color::White);
        TiledWindow& putString(const std::string& str, int x, int y, int width, AlignmentX alignment = AlignmentX::Left, int offset = 0, const sf::Color& color = sf::Color::White);
        //////////////////// Sprite drawing
        TiledWindow& putSprite(const sf::Sprite& sprite);
        TiledWindow& putSprite(const sf::Sprite& sprite, int x, int y);
        TiledWindow& putSprite(const sf::Sprite& sprite, const sf::IntRect& bound);
        TiledWindow& putSprite(const sf::Sprite& sprite, int x, int y, int width, int height);
        //////////////////// Single char drawing
        TiledWindow& putChar(char c, const sf::Color& color = sf::Color::White);
        TiledWindow& putChar(char c, int x, int y, const sf::Color& color = sf::Color::White);
        TiledWindow& putSpecialChar(int c, const sf::Color& color = sf::Color::White);
        TiledWindow& putSpecialChar(int c, int x, int y, const sf::Color& color = sf::Color::White);
        //////////////////// Border drawing
        void drawEdgeBorder(const sf::Color& color = sf::Color::White);
        void drawCenterBorder(const sf::Color& color = sf::Color::White);
        //////////////////// Box drawing.
        void drawCenterBox(const sf::IntRect& bound, const sf::Color& color = sf::Color::White);
        void drawEdgeBox(const sf::IntRect& bound, const sf::Color& color = sf::Color::White);
        //////////////////// filling.
    };
}
#endif
