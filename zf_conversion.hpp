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
#ifndef _ZFRAMEWORK_ZF_CONVERSION_HPP_
#define _ZFRAMEWORK_ZF_CONVERSION_HPP_
/**
 * zf_conversion dependency :
 *      .1 zf_strings.hpp:
 */
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
namespace zf
{
    //////////////////// Primitives ////////////////////
    /**
     * convert a string to a int, and place it in value.
     * return true if successful, false otherwise.
     * value is not changed if not successful.
     */
    bool stringToInt(const std::string& str, int& value);

    std::string intToString(int value);

    /**
     * convert a string to a bool, and place it in value.
     * return true if successul, false otherwise.
     * value is not changed if not successful
     */
    bool stringToBool(const std::string& str, bool& value);

    /**
     * convert a bool to a string.
     * convert true to "true" and false to "false"
     */
    std::string boolToString(bool value);
    
    std::string floatToString(float value, unsigned int numDecimal);

    std::string rectToString(const sf::IntRect& rect);
    std::string vector2iToString(const sf::Vector2i& vect);
    bool stringToVector2i(const std::string& str, sf::Vector2i& value);
}

#endif
