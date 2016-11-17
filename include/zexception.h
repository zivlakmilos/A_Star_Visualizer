#ifndef _Z_EXCEPTION_H_
#define _Z_EXCEPTION_H_

#include <exception>
#include <string>

class ZException : public std::exception
{
public:
    ZException(std::string what = "");
    virtual ~ZException(void);
    
    virtual const char *what(void) const throw() override;
    
private:
    std::string m_what;
};

#endif // _Z_EXCEPTION_H_
