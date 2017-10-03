/* 
 * File:   newsimpletest.cpp
 * Author: rnetuka
 *
 * Created on 21. října 2016, 15:53
 */

#include <iostream>

#include "mac.h"

using namespace std;


void test_mac_address_equal() 
{
    MacAddress address(0xe82aea1ef78a);
    MacAddress other(0xe82aea1ef78a);
    
    if (! (address == other)) 
    {
        cout << "%TEST_FAILED% ";
        cout << "time=0 ";
        cout << "testname=test_mac_address_equal (mac_constructor_test) ";
        cout << "message=";
        cout << endl;
    }
}

int main()
{
    cout << "%SUITE_STARTING% mac_equality_test" << endl;
    cout << "%SUITE_STARTED%" << endl;

    cout << "%TEST_STARTED% test_mac_address_equal (newsimpletest)" << endl;
    test_mac_address_equal();
    cout << "%TEST_FINISHED% time=0 test_mac_address_equal (newsimpletest)" << endl;

    cout << "%SUITE_FINISHED% time=0" << endl;

    return 0;
}

