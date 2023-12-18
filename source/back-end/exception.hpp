#ifndef EXC_H
#define EXC_H

/*
--------------------------------------------------
  ______                    _   _
 |  ____|                  | | (_)
 | |__  __  _____ ___ _ __ | |_ _  ___  _ __  ___
 |  __| \ \/ / __/ _ \ '_ \| __| |/ _ \| '_ \/ __|
 | |____ >  < (_|  __/ |_) | |_| | (_) | | | \__ \
 |______/_/\_\___\___| .__/ \__|_|\___/|_| |_|___/
                     | |
                     |_|
--------------------------------------------------
*/

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
