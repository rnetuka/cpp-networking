/*
 */

#include <ostream>
#include <string>

#include "version.h"

using namespace http;
using namespace std;


Version::Version(int major, int minor) : major_(major), minor_(minor)
{
    
}

ostream& operator <<(ostream& stream, const Version& version)
{
    return stream << "HTTP/" << major << '.' << minor;
}