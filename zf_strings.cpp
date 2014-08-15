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
