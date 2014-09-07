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
#ifndef _ZFRAMEWORK_ZF_STRINGFORMAT_HPP_
#define _ZFRAMEWORK_ZF_STRINGFORMAT_HPP_
/** 
 * zf_stringformat dependency
 *      .1 zf_conversion
 *      .2 zf_strings
 */
#include <string>
namespace zf
{
    /**
     * currently supports
     *      %s for string
     *      %i for int
     *      %c for char
     *      %f for float
     * 
     * Uses the conversion method in zf_conversion to work,
     * doesn't care about single character %
     * escaped % will not be replaced.
     */
    class Format
    {
    public:
        Format(const std::string& str);

        Format& operator%(int i);
        Format& operator%(char c);
        Format& operator%(const std::string& str);

        std::string str;
    };

    Format format(const std::string& str);
};
#endif
