#include <iostream>
#include <string>

#include "ipv4_address.h"

using namespace std;
using namespace ipv4;


void test_address_string() 
{
    Address address(255, 127, 0, 11);
    
    string expected = "255.127.0.11";
    string result = address.str();
    
    if (result != expected)
    {
        cout << "%TEST_FAILED% ";
        cout << "time=0 ";
        cout << "testname=test_address_string (ipv6_address_test) ";
        cout << "message=";
        cout << "Expected: " << expected << ", but got " << address;
        cout << endl;
    }
}

int main() 
{
    cout << "%SUITE_STARTING% ipv4_address_construction_test" << endl;
    cout << "%SUITE_STARTED%" << endl;

    cout << "%TEST_STARTED% test_address_string (ipv4_address_test)" << endl;
    test_address_string();
    cout << "%TEST_FINISHED% time=0 test_address_string (ipv4_address_test)" << endl;

    cout << "%SUITE_FINISHED% time=0" << endl;
    return 0;
}

