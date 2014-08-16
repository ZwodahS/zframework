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
#include "zf_strings.hpp"
#include <sstream>
namespace zf_strings
{
    /**
     * These 2 functions are taken from
     * http://stackoverflow.com/questions/236129/how-to-split-a-string-in-c
     */
    std::vector<std::string>& split(const std::string &s, char delim, std::vector<std::string> &elems) 
    {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) 
        {
            elems.push_back(item);
        }
        return elems;
    }


    std::vector<std::string> split(const std::string &s, char delim) 
    {
        std::vector<std::string> elems;
        split(s, delim, elems);
        return elems;
    }
    /**
     * Split a single strings into multiple strings, 
     * each string in the return list have a maximum characters of "maxChar"
     */
    std::vector<std::string> splitString(const std::string& str, int maxChar)
    {
        std::vector<std::string> strings;
        std::vector<std::string> tokens = split(str, ' ');
        std::string curr = "";
        int token = 0 ;
        for (std::vector<std::string>::iterator it = tokens.begin() ; it != tokens.end() ; ++it)
        {
            if (curr.size() + 1 + (*it).size() > maxChar)
            {
                if (token == 0)
                {
                    token = 0;
                    strings.push_back(*it);
                }
                else
                {
                    strings.push_back(curr);
                    curr = "";
                    curr += *it;
                    token = 1;
                }
            }
            else
            {
                if (token != 0)
                {
                    curr += " ";
                }
                curr += *it;
                token++;
            }
        }
        if (token != 0)
        {
            strings.push_back(curr);
        }
        return strings;
    }

    bool startsWith(const std::string& longStrings, const std::string& startString)
    {
        std::size_t index = longStrings.find(startString);
        return index == 0;
    }
}
