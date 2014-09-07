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
#include "zf_rect.hpp"
namespace zf
{
    //////////////////// Utility methods ////////////////////
    int rightOf(const sf::IntRect& rect)
    {
        return rect.left + rect.width - 1;
    }

    int bottomOf(const sf::IntRect& rect)
    {
        return rect.top + rect.height - 1;
    }

    int leftOf(const sf::IntRect& rect)
    {
        return rect.left;
    }

    int topOf(const sf::IntRect& rect)
    {
        return rect.top;
    }

    sf::IntRect& move(sf::IntRect& rect, const sf::Vector2i& moveVect)
    {
        rect.left += moveVect.x;
        rect.top += moveVect.y;
        return rect;
    }

    sf::IntRect moveCopy(sf::IntRect rect, const sf::Vector2i& moveVect)
    {
        return move(rect, moveVect);
    }

    sf::IntRect& setRectByCorners(sf::IntRect& rect, int left, int top, int right, int bottom)
    {
        rect.left = left;
        rect.top = top;
        rect.width = right - left + 1;
        rect.height = bottom - top + 1;
        return rect;
    }

    sf::IntRect& fitRectByShrinking(sf::IntRect& innerRect, const sf::IntRect& outerRect)
    {
        int iLeft = leftOf(innerRect);
        int iRight = rightOf(innerRect);
        int iTop = topOf(innerRect);
        int iBottom = bottomOf(innerRect);
        int oLeft = leftOf(outerRect);
        int oRight = rightOf(outerRect);
        int oTop = topOf(outerRect);
        int oBottom = bottomOf(outerRect);
        iLeft = iLeft < oLeft ? oLeft : iLeft;
        iRight = iRight > oRight ? oRight : iRight;
        iTop = iTop < oTop ? oTop : iTop;
        iBottom = iBottom > oBottom ? oBottom : iBottom;
        return setRectByCorners(innerRect, iLeft, iTop, iRight, iBottom);
    }
    
    
    sf::IntRect centerRect(const sf::IntRect& rect, const sf::IntRect& referenceRect)
    {
        // calculate the spare space.
        int spareX = referenceRect.width - rect.width;
        int spareY = referenceRect.height - rect.height;
        return sf::IntRect(referenceRect.left + spareX / 2, referenceRect.top + spareY / 2, rect.width, rect.height);
    }

    sf::FloatRect& alignRect(sf::FloatRect& rect, AlignmentX xAlignment, AlignmentY yAlignment, const sf::Vector2f& target, const sf::Vector2f& offset)
    {
        if (xAlignment == AlignmentX::Left)
        {
            rect.left = target.x + offset.x;
        }
        else if (xAlignment == AlignmentX::Right)
        {
            rect.left = target.x - offset.x - rect.width;
        }
        else if (xAlignment == AlignmentX::Center)
        {
            rect.left = target.x - offset.x - rect.width / 2;
        }
        
        if (yAlignment == AlignmentY::Top)
        {
            rect.top = target.y + offset.y;
        }
        else if (yAlignment == AlignmentY::Bottom)
        {
            rect.top = target.y - offset.y - rect.height;
        }
        else if (yAlignment == AlignmentY::Center)
        {
            rect.top = target.y - offset.y - rect.height / 2;
        }
        return rect;
    }
}
