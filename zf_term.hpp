#ifndef _ZFRAMEWORK_ZF_TERM_HPP
#define _ZFRAMEWORK_ZF_TERM_HPP
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
/***
 * zf_term dependency :
 *      .1 zf_spritesheet.hpp
 *
 */
#include "zf_spritesheet.hpp"
namespace zf
{
    //////////////////// special characters are used in term screen ////////////////////
    extern const int NORTH_BIT, EAST_BIT, SOUTH_BIT, WEST_BIT;
    extern const int Border[16];
    extern const int Cross[16];
    extern const int Center_dot;
    extern const int Diagonal[2];
    extern const int Alternate[2];
    extern const int Fill;
    extern const int TotalSpecialChar;

    //////////////////// Utility Methods ////////////////////
    /**
     * Get the right of the rect
     */
    int rightOf(const sf::IntRect& rect);
    /**
     * Get the bottom of the rect.
     */
    int bottomOf(const sf::IntRect& rect);
    /**
     * For completeness sake
     */
    int leftOf(const sf::IntRect& rect);
    int topOf(const sf::IntRect& rect);

    /**
     * Try to fix the inner rect into out rect.
     * This fit the inner rect using shrinking.
     */
    sf::IntRect& fitRectByShrinking(sf::IntRect& innerRect, const sf::IntRect& outerRect);
    //////////////////// TermCell ////////////////////
    /**
     * A single cell in the terminal.
     * There are a few things that can be displayed and customized.
     */
    struct TermCell
    {
        /**
         * For now we will use sprite. Might change to render states and texture stuffs later.
         */
        sf::Sprite foreground;
        sf::Sprite background;
        TermCell(const sf::Sprite& foreground = sf::Sprite(), const sf::Sprite& background = sf::Sprite());
    };
    class TermScreen;
    //////////////////// TermWindow ////////////////////
    class TermWindow
    {
    public:
        TermWindow(TermScreen& screen); 
        ~TermWindow();

        friend TermScreen; 
        
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


        /**
         * Put a string onto the screen. It is always placed at the foreground.
         */
        void putString(const std::string& str);
        void putString_xy(int x, int y, const std::string& str);
         
        const bool& isVisible() const;

        /**
         * Draw border
         */
        void drawEdgeBorder();
        void drawCenterBorder();
        void hide();
        void show();
    private:
        void updateScreen();
        TermScreen& screen;
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
    //////////////////// TermScreen ////////////////////
    /**
     * The core screen.
     */
    class TermScreen
    {
    public:
        const TextureRegion emptyRegion = TextureRegion();
        /** 
         * window defines the window that is used.
         * termSize defines the number of rows and columns
         */
        TermScreen(sf::RenderWindow& window, const sf::Vector2i& termSize);
        ~TermScreen();

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
        void init(const sf::Vector2i& cellSize, const sf::Vector2i& spriteSize);
        
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
         */
        void updateRenderWindow();

        /**
         * Create a new window in this region.
         * If the window is out of bound, it will automatically resize itself to fit in.
         */
        TermWindow& newWindow(const sf::IntRect& bound);
        TermWindow& newWindow(int x, int y, int width, int height);

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
        bool addChar(char c, const sf::Image& image);
        TextureRegion getChar(char c);

        bool addSpecialChar(int c, const sf::Image& image);
        TextureRegion getSpecialChar(int c);
    private:
        /**
         * directly put this cell into this position.
         */
        void directPut(const TermCell& cell, int x, int y);
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
