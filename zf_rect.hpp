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
#ifndef _ZFRAMEWORK_ZF_RECT_HPP_
#define _ZFRAMEWORK_ZF_RECT_HPP_
#include <string>
#include <SFML/Graphics.hpp>
/**
 * zf_rect dependency :
 *      .1 zf_alignment.hpp
 */
#include "zf_alignment.hpp"
namespace zf
{
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

    sf::IntRect& move(sf::IntRect& rect, const sf::Vector2i& moveVect);
    sf::IntRect moveCopy(sf::IntRect rect, const sf::Vector2i& moveVect);
    
    sf::IntRect& setRectByCorners(sf::IntRect& rect, int left, int top, int right, int bottom);
    /**
     * Try to fix the inner rect into outer rect.
     * This fit the inner rect using shrinking.
     */
    sf::IntRect& fitRectByShrinking(sf::IntRect& innerRect, const sf::IntRect& outerRect);

    /**
     * Center the rect with respect to referenceRect.
     */
    sf::IntRect centerRect(const sf::IntRect& rect, const sf::IntRect& referenceRect);

    sf::FloatRect& alignRect(sf::FloatRect& rect, AlignmentX xAlignment, AlignmentY yAlignment, const sf::Vector2f& target, const sf::Vector2f& offset = sf::Vector2f(0, 0));
}
#endif
