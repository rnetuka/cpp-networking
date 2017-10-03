/* 
 * File:   network.h
 * Author: rnetuka
 *
 * Created on 21. října 2016, 14:28
 */

#ifndef NETWORK_H
#define NETWORK_H

#include <mac.h>
#include <net/interface.h>


namespace net
{

    Interface default_interface();
    Interface backup_interface();
    Interface active_interface();

}

#endif

