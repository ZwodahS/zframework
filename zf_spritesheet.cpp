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
#include "zf_spritesheet.hpp"
namespace zf
{
    //////////////////// TextureRegion ////////////////////
    TextureRegion::TextureRegion(sf::Texture* t, const sf::IntRect& s, const sf::Color& d)
        :texture(t), srcClip(s), defaultColor(d)
        , defaultScaleX(1), defaultScaleY(1)
    {
    }

    sf::Sprite TextureRegion::createSprite() const
    {
        if(texture == nullptr)
        {
            return sf::Sprite();
        }
        sf::Sprite sprite(*texture, srcClip);
        sprite.setColor(defaultColor);
        sprite.setScale(defaultScaleX, defaultScaleY);
        return sprite;
    }

    //////////////////// SpriteSheet ////////////////////
    SpriteSheet::SpriteSheet()
        : texture(nullptr), bound(0, 0, 0, 0), managed(false), spriteSize(0, 0, 0, 0), currRow(0), currCol(0), maxRow(0), maxCol(0)
    {
    }

    SpriteSheet::SpriteSheet(sf::Texture* t, const sf::IntRect& b)
        : texture(t), bound(b), managed(false), spriteSize(0, 0, 0, 0), currRow(0), currCol(0), maxRow(0), maxCol(0)
    {
    }

    SpriteSheet::SpriteSheet(sf::Texture* t, const sf::IntRect& b, const sf::IntRect& s, int row, int col)
        : texture(t), bound(b), managed(true), spriteSize(s), currRow(0), currCol(0), maxRow(row), maxCol(col)
    {
    }

    void SpriteSheet::create(sf::Texture* t, const sf::IntRect& b)
    {
        managed = false;
        currRow = 0;
        currCol = 0;
        maxRow = 0;
        maxCol = 0;
        texture = t;
        bound = b;
        spriteSize = sf::IntRect(0,0,0,0);
    }

    void SpriteSheet::create(sf::Texture* t, const sf::IntRect& b, const sf::IntRect& s, int row, int col)
    {
        managed = true;
        currRow = 0;
        currCol = 0;
        maxRow = row;
        maxCol = col;
        texture = t;
        bound = b;
        spriteSize = s;
    }

    TextureRegion SpriteSheet::addImage(const sf::Image& image, const sf::Color& defaultColor)
    {
        if(managed)
        {
            const sf::Vector2u imgSize = image.getSize();
            if(imgSize.x != this->spriteSize.width || imgSize.y != this->spriteSize.height)
            {
                return TextureRegion(); 
            }
            const sf::IntRect targetBound(currCol * spriteSize.width, currRow * spriteSize.height, spriteSize.width, spriteSize.height);
            TextureRegion returnRegion = internal_createRegion(image, targetBound);
            currCol++;
            if(currCol >= maxCol)
            {
                currCol = 0;
                currRow++;
                if(currRow >= maxRow)
                {
                    currRow = 0; //just wrap it back. graphics error is better than runtime.
                }
            }
            returnRegion.defaultColor = defaultColor;
            return returnRegion;
        }
        else
        {
            TextureRegion r = addImage(image,0,0);
            r.defaultColor = defaultColor;
            return r;
        }
    }

    TextureRegion SpriteSheet::addImage(const sf::Image& image, int x , int y, const sf::Color& defaultColor)
    {
        sf::Vector2u imgSize = image.getSize();
        TextureRegion returnRegion = internal_createRegion(image, sf::IntRect(x, y, imgSize.x, imgSize.y));
        returnRegion.defaultColor = defaultColor;
        return returnRegion;
    }

    TextureRegion SpriteSheet::createRegion(int x, int y, int w, int h, const sf::Color& defaultColor)
    {
        TextureRegion r = internal_createRegion(sf::IntRect(x, y, w, h));
        r.defaultColor = defaultColor;
        return r;
    }

    TextureRegion SpriteSheet::createRegion(const sf::IntRect& region, const sf::Color& defaultColor)
    {
        TextureRegion r = internal_createRegion(region);
        r.defaultColor = defaultColor;
        return r;
    }

    SpriteSheet SpriteSheet::createSubSheet(sf::IntRect newBound)
    {
        newBound.top += bound.top;
        newBound.left += bound.left;
        return SpriteSheet(texture, newBound);
    }

    SpriteSheet SpriteSheet::createSubSheet(const sf::Vector2i& position, const sf::IntRect& spriteSize, int row, int col)
    {
        sf::IntRect newBound(position.x + bound.left , position.y + bound.top, row * spriteSize.width , col * spriteSize.height);
        return SpriteSheet(texture, newBound, spriteSize, row, col);
    }

    TextureRegion SpriteSheet::internal_createRegion(const sf::Image& image, sf::IntRect region)
    {
        if(texture == nullptr)
        {
            return TextureRegion();
        }
        region.top += bound.top;
        region.left += bound.left;
        texture->update(image, region.left, region.top);
        return TextureRegion(texture, region);
    }

    TextureRegion SpriteSheet::internal_createRegion(sf::IntRect region)
    {
        if(texture == nullptr)
        {
            return TextureRegion();
        }
        region.top += bound.top;
        region.left += bound.left;
        return TextureRegion(texture, region);
    }
}
