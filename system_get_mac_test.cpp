/* 
 * File:   system_get_mac_test.cpp
 * Author: rnetuka
 *
 * Created on 21. října 2016, 16:28
 */

#include <iostream>

#include "mac.h"
#include "system.h"

using namespace std;


void test_get_device_mac_address() 
{
    MacAddress result = mac_address("wlp4s0");
    MacAddress expected = MacAddress::parse("e8:2a:ea:1e:f7:8a");
    
    if (result != expected) 
    {
        cout << "%TEST_FAILED% ";
        cout << "time=0 ";
        cout << "testname=test_get_device_mac_address (mac_constructor_test) ";
        cout << "message=Expected: " << expected << " but got: " << result << " instead.";
        cout << endl;
    }
}

int main() 
{
    cout << "%SUITE_STARTING% system_get_mac_test" << endl;
    cout << "%SUITE_STARTED%" << endl;

    cout << "%TEST_STARTED% test_get_device_mac_address (system_get_mac_test)" << endl;
    test_get_device_mac_address();
    cout << "%TEST_FINISHED% time=0 test_get_device_mac_address (system_get_mac_test)" << endl;

    cout << "%SUITE_FINISHED% time=0" << endl;

    return 0;
}

