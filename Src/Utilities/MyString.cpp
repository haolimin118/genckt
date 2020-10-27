#include "MyString.h"
#include <sstream>

std::string STR(int n)
{
    return std::to_string(n);
}

std::string STR(double d)
{
    std::stringstream ss;
    ss << d;
    return ss.str();
}