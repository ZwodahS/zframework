#ifndef _ZFRAMEWORK_ZF_CONVERSION_HPP_
#define _ZFRAMEWORK_ZF_CONVERSION_HPP_
#include <vector>
#include <string>
namespace zf_conversion
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
}

#endif
