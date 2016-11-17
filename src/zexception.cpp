#include "zexception.h"

ZException::ZException(std::string what)
    : m_what(what)
{
}

ZException::~ZException(void)
{
}

const char *ZException::what(void) const throw()
{
    return m_what.c_str();
}
