/*
 */

/* 
 * File:   version.h
 * Author: rnetuka
 *
 * Created on 8. listopadu 2016, 15:32
 */

#ifndef VERSION_H
#define VERSION_H

#include <ostream>

namespace http
{
    
    class Version
    {
    private:
        int major_;
        int minor_;
        
    public:
        Version(int major, int minor);
        
        friend std::ostream& operator <<(std::ostream& stream, const Version& version);
    };
    
}

#endif /* VERSION_H */

