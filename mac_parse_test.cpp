/* 
 * File:   mac_parse_test.cpp
 * Author: rnetuka
 *
 * Created on 21. října 2016, 15:50
 */

#include <iostream>
#include <string>

#include "mac.h"

using namespace std;


void test_parse_mac_address() 
{
    MacAddress result = MacAddress::parse("e8:2a:ea:1e:f7:8a");
    MacAddress expected(0xe82aea1ef78a);
    
    if (result != expected) 
    {
        cout << "%TEST_FAILED% ";
        cout << "time=0 ";
        cout << "testname=test_parse_mac_address (mac_constructor_test) ";
        cout << "message=Expected: " << expected << " but got: " << result;
        cout << endl;
    }
}

int main() 
{
    cout << "%SUITE_STARTING% mac_parse_test" << endl;
    cout << "%SUITE_STARTED%" << endl;

    cout << "%TEST_STARTED% test_parse_mac_address (mac_parse_test)" << endl;
    test_parse_mac_address();
    cout << "%TEST_FINISHED% time=0 test_parse_mac_address (mac_parse_test)" << endl;

    cout << "%SUITE_FINISHED% time=0" << endl;

    return 0;
}

