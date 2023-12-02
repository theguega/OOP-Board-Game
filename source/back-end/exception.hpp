#ifndef EXC_H
#define EXC_H

#include <iostream>
#include <string>

class SplendorException{
private:
    std::string info;
public:
    SplendorException(const std::string& i) : info(i) {}
    std::string getInfo() const { return info; }
};


#endif
