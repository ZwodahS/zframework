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
#include <sstream>
namespace conversion
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
        if (str != std::to_string(temp)) //if the converted value is different then return 0 (similar to atoi)
        {
            return false;
        }
        value = temp;
        return true;
    }

    std::string intToString(int value)
    {
        // TODO Might need to fix for some compiler with weird c++11 behavior.
        return std::to_string(value);
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
        int max = 100;
        for(int i = 0; i < numDecimal; i++)
        {
            max *= 10;
        }
        int p = value * max;
        std::string out = std::to_string(p);
        if (numDecimal != 0)
        {
            out.insert(out.size() - numDecimal, ".");
        }
        return out;
    }
}
