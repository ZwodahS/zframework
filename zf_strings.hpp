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

#ifndef _ZFRAMEWORK_ZF_STRINGS_HPP_
#define _ZFRAMEWORK_ZF_STRINGS_HPP_
#include <string>
#include <vector>
namespace zf_strings
{
    /**
     * Split a strings by a delimiter
     */
    std::vector<std::string>& split(const std::string &s, char delim, std::vector<std::string> &elems);
    std::vector<std::string> split(const std::string &s, char delim);
    /**
     * Split a single strings into multiple strings, 
     * each string in the return list have a maximum characters of "maxChar"
     */
    std::vector<std::string> splitString(const std::string& str, int maxChar);
    
    /**
     * Check if longString starts with startString.
     */
    bool startsWith(const std::string& longString, const std::string& startString);
}
#endif
