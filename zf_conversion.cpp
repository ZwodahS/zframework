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
