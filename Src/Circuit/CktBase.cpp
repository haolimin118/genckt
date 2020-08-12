#include "CktBase.h"
#include "Utilities/MyString.h"

CktBase::CktBase(int scale, const std::string &typeName)
{
    m_scale = scale;
    m_typeName = typeName;
    m_title = typeName + " --scale=" + STR(scale);
}