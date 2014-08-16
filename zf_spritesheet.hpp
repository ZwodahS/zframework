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
#ifndef _ZFRAMEWORK_ZF_SPRITESHEET_HPP_
#define _ZFRAMEWORK_ZF_SPRITESHEET_HPP_
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
/**
 * zf_spritesheet have 2 structure.
 * The first is a struct that defines a region in a texture.
 * This is primarily used in the spritesheet class to define regions.
 *
 * The second is a SpriteSheet class.
 * This is the core of this module.
 *
 * SpriteSheet help you compile image on runtime into a single texture.
 * How to combine is really up to you. 
 * You could write an algorithm to pack it on runtime for you for all I care.
 *
 * It doesn't do much bound checks, to give you maximum flexibility.
 *
 * SpriteSheet als allow you to create a sheet that have fixed spritesize.
 * If you choose to do so, the spritesheet will also control the location for you.
 */
namespace zf
{
    /**
     * Defines a texture region for a texture.
     * Use in spritesheet to manage the different region of the texture.
     */
    struct TextureRegion
    {
        sf::Texture* texture;
        sf::IntRect srcClip;
        sf::Color defaultColor;
        float defaultScaleX;
        float defaultScaleY;
        TextureRegion(sf::Texture* t = nullptr, const sf::IntRect& srcClip = sf::IntRect(0, 0, 0, 0) , const sf::Color& defaultColor = sf::Color::White);

        sf::Sprite createSprite() const;
    };

    /**
     * The core spritesheet cass
     */
    class SpriteSheet
    {
    public:
        SpriteSheet(); // empty spritesheet.
        /**
         * Create a spritesheet with this texture. the bound define the region that can be used.
         * There is no bound checking. Just make sure you know what you are doing.
         * The create method just create it if you already created the empty spritesheet.
         * The sprite sheet do not manage the texture. You need to free it yourself.
         */
        SpriteSheet(sf::Texture* texture, const sf::IntRect& bound);
        void create(sf::Texture* texture, const sf::IntRect& bound);
        SpriteSheet(sf::Texture* texture, const sf::IntRect& bound, const sf::IntRect& spriteSize, int row, int col);
        void create(sf::Texture* texture, const sf::IntRect& bound, const sf::IntRect& spriteSize, int row, int col);

        /**
         * Create region at the current position. If this spritesheet is managed, then it will be slot at the correct position.
         * If the spritesheet is not managed, then it will be the same as createRegion(image,0,0);
         */
        TextureRegion addImage(const sf::Image& image, const sf::Color& defaultColor = sf::Color(255,255,255,255));
        TextureRegion addImage(const sf::Image& image, int x , int y, const sf::Color& defaultColor = sf::Color(255,255,255,255));
        TextureRegion createRegion(int x, int y, int w, int h, const sf::Color& defaultColor = sf::Color(255,255,255,255));
        TextureRegion createRegion(const sf::IntRect& region, const sf::Color& defaultColor = sf::Color(255,255,255,255));
        // Note that the region that the sprite is created is always relative to the origin bound that is specified.
        // i.e. if this sprite sheet is created with bound = (100,100,500,500),
        // then when createRegion(image) is called, the image will be added to sf::Vector2i(100,100) 
        // and the region that is returned will be at (100,100,w,h) where w = width of image, and h = height of image.
        //
        SpriteSheet createSubSheet(sf::IntRect bound);
        SpriteSheet createSubSheet(const sf::Vector2i& position , const sf::IntRect& spriteSize, int row , int col);
    private:     
        sf::Texture* texture;
        sf::IntRect bound;

        // for managed spriteSheet. Managed SpriteSheet means that the size in that spritesheet is the same and when createRegion is called, it will be added to the correct slot
        // and the correct region will be returned.
        bool managed;
        sf::IntRect spriteSize;
        int currRow;
        int currCol;
        int maxRow;
        int maxCol;
        
        TextureRegion internal_createRegion(const sf::Image& image, sf::IntRect region);
        TextureRegion internal_createRegion(sf::IntRect region);
    };
}
#endif
