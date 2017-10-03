/*
 */

#include <fstream>
#include <string>

#include <mac.h>
#include <net/interface.h>

#include "network.h"

using namespace mac;
using namespace std;

const string path = "/sys/class/net/";


namespace net
{
    
    Interface default_interface()
    {
        return Interface("em1");
    }

    Interface backup_interface()
    {
        return Interface("wlp4s0");
    }

    Interface active_interface()
    {
        Interface default_interface_ = default_interface();
        Interface backup_interface_ = backup_interface();
        return default_interface_.up() ? default_interface_ : backup_interface_;
    }

}
    