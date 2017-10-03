/* 
 * File:   mac_constructor_test.cpp
 * Author: rnetuka
 *
 * Created on 21. října 2016, 15:53
 */

#include <cstdint>
#include <iostream>

#include "mac.h"

using namespace std;


void test_create_mac_address() 
{
    MacAddress address(0xe82aea1ef78a);
    
    if (address[0] != 0xe8
        || address[1] != 0x2a
        || address[2] != 0xea
        || address[3] != 0x1e
        || address[4] != 0xf7
        || address[5] != 0x8a) 
    {
        cout << "%TEST_FAILED% ";
        cout << "time=0 ";
        cout << "testname=test_create_mac_address (mac_constructor_test) ";
        cout << "message=Assertion failed: " << address;
        cout << endl;
    }
}

int main()
{
    cout << "%SUITE_STARTING% mac_constructor_test" << endl;
    cout << "%SUITE_STARTED%" << endl;

    cout << "%TEST_STARTED% test_create_mac_address (mac_constructor_test)" << endl;
    test_create_mac_address();
    cout << "%TEST_FINISHED% time=0 test_create_mac_address (mac_constructor_test)" << endl;

    cout << "%SUITE_FINISHED% time=0" << endl;
    return 0;
}

