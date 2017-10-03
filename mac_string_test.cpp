/* 
 * File:   mac_string_test.cpp
 * Author: rnetuka
 *
 * Created on 21. října 2016, 15:52
 */

#include <iostream>
#include <string>

#include "mac.h"

using namespace std;


void test_mac_address_to_string() 
{
    MacAddress address(0xe82aea1ef78a);
    
    string result = address.str();
    string expected = "e8:2a:ea:1e:f7:8a";
    
    if (result != expected) 
    {
        cout << "%TEST_FAILED% ";
        cout << "time=0 ";
        cout << "testname=test_mac_address_to_string (mac_constructor_test) ";
        cout << "message=Expected: " << expected << " but got: " << result;
        cout << endl;
    }
}

int main() 
{
    cout << "%SUITE_STARTING% mac_string_test" << endl;
    cout << "%SUITE_STARTED%" << endl;

    cout << "%TEST_STARTED% test_mac_address_to_string (mac_string_test)" << endl;
    test_mac_address_to_string();
    cout << "%TEST_FINISHED% time=0 test_mac_address_to_string (mac_string_test)" << endl;

    cout << "%SUITE_FINISHED% time=0" << endl;
    return 0;
}

