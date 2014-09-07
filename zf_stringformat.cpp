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
#include "zf_stringformat.hpp"
#include "zf_conversion.hpp"
#include "zf_strings.hpp"

namespace zf
{
    Format::Format(const std::string& str)
        : str(str)
    {
    }

    Format format(const std::string& str)
    {
        return Format(str);
    }

    Format& Format::operator%(int i)
    {
        std::string s = intToString(i);
        replaceString(str, "%i", s, false);
        return *this;
    }

    Format& Format::operator%(char c)
    {
        std::string s = charToString(c);
        replaceString(str, "%c", s, false);
        return *this;
    }

    Format& Format::operator%(const std::string& s)
    {
        replaceString(str, "%s", s, false);
        return *this;
    }

}
