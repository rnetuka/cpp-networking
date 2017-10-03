/*
 */

#include <iostream>
#include <string>

#include "ipv6_address.h"

using namespace std;
using namespace ipv6;


void test_address_to_string()
{
    Address address(0x2001, 0x0DB8, 0xAC10, 0xFE01, 0x0000, 0x0000, 0x0000, 0x0000);
    
    string expected = "2001:0db8:ac10:fe01:0000:0000:0000:0000";
    string result = address.str();
    
    if (result != expected)
    {
        cout << "%TEST_FAILED% ";
        cout << "time=0 ";
        cout << "testname=test_address_to_string (ipv6_address_test) ";
        cout << "message=";
        cout << "Expected: " << expected << ", but got " << result;
        cout << endl;
    }
}

int main() 
{
    cout << "%SUITE_STARTING% ipv6_address_string_test" << endl;
    cout << "%SUITE_STARTED%" << endl;

    cout << "%TEST_STARTED% test_address_to_string (ipv6_address_test)" << endl;
    test_address_to_string();
    cout << "%TEST_FINISHED% time=0 test_address_to_string (ipv6_address_test)" << endl;

    cout << "%SUITE_FINISHED% time=0" << endl;
    return 0;
}