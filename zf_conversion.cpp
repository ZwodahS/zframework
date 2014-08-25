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
#include "zf_conversion.hpp"
#include "zf_strings.hpp"
#include <sstream>
namespace zf
{
    /**
     * This method originate from another file
     * http://github.com/ZwodahS/z_framework
     *    /zf_common/f_conversion.hpp
     */
    bool stringToInt(const std::string& str, int& value)
    {
        std::istringstream buffer(str);
        int temp;
        buffer >> temp;
        if (str != intToString(temp)) //if the converted value is different then return 0 (similar to atoi)
        {
            return false;
        }
        value = temp;
        return true;
    }

    std::string intToString(int value)
    {
#ifdef NO_STD_TO_STRING
        std::stringstream sstr;
        sstr << value;
        return sstr.str();
#else
        return std::to_string(value);
#endif

    }

    bool stringToBool(const std::string& str, bool& value)
    {
        if (str == "true")
        {
            value = true;
            return true;
        }
        else if(str == "false")
        {
            value = false;
            return true;
        }
        return false;
    }

    std::string boolToString(bool value)
    {
        return value ? "true" : "false";
    }

    /**
     * Quite sure there is a better way to do this, but heck do it later ..
     */
    std::string floatToString(float value, unsigned int numDecimal)
    {
        int max = 1;
        for(int i = 0; i < numDecimal; i++)
        {
            max *= 10;
        }
        int p = value * max;
        std::string out = intToString(p);
        if (numDecimal != 0)
        {
            out.insert(out.size() - numDecimal, ".");
        }
        return out;
    }

    std::string rectToString(const sf::IntRect& rect)
    {
        return intToString(rect.left) + " " + intToString(rect.top) + " " + intToString(rect.width) + " " + intToString(rect.height);
    }

    std::string vector2iToString(const sf::Vector2i& vect)
    {
        return intToString(vect.x) + "," + intToString(vect.y);
    }

    bool stringToVector2i(const std::string& str, sf::Vector2i& value)
    {
        auto split = zf::splitStringByDelimiter(str, ',');
        if (split.size() != 2)
        {
            return false;
        }
        int x, y;
        if (!stringToInt(split[0], x) || !stringToInt(split[1], y))
        {
            return false;
        }
        value.x = x;
        value.y = y;
        return true;
    }
}
