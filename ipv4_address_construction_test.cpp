/*
 *
 */

#include <cstdint>
#include <iostream>

#include "ipv4_address.h"

using namespace std;
using namespace ipv4;


void test_address_from_full_string() 
{
    Address address("255.127.0.11");
    Address expected(255, 127, 0, 11);
    
    if (address != expected)
    {
        cout << "%TEST_FAILED% ";
        cout << "time=0 ";
        cout << "testname=test_address_from_full_string (ipv6_address_test) ";
        cout << "message=";
        cout << "Expected: " << expected << ", but got " << address;
        cout << endl;
    }
}

void test_create_from_number()
{
    // b11111111_01111111_00000000_00001011
    Address address(4286513163ul);
    Address expected(255, 127, 0, 11);
    
    if (address != expected)
    {
        cout << "%TEST_FAILED% ";
        cout << "time=0 ";
        cout << "testname=test_address_from_full_string (ipv6_address_test) ";
        cout << "message=";
        cout << "Expected: " << expected << ", but got " << address;
        cout << endl;
    }
}

int main() 
{
    cout << "%SUITE_STARTING% ipv4_address_construction_test" << endl;
    cout << "%SUITE_STARTED%" << endl;

    cout << "%TEST_STARTED% test_address_from_full_string (ipv4_address_test)" << endl;
    test_address_from_full_string();
    cout << "%TEST_FINISHED% time=0 test_address_from_full_string (ipv4_address_test)" << endl;
    
    cout << "%TEST_STARTED% test_create_from_number (ipv4_address_test)" << endl;
    test_create_from_number();
    cout << "%TEST_FINISHED% time=0 test_create_from_number (ipv4_address_test)" << endl;

    cout << "%SUITE_FINISHED% time=0" << endl;
    return 0;
}