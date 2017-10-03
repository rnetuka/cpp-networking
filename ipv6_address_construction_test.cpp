/* 
 * File:   ipv6_address_test.cpp
 * Author: rnetuka
 *
 * Created on 4. října 2016, 15:22
 */

#include <iostream>

#include "ipv6_address.h"

using namespace std;
using namespace ipv6;


void test_address_from_full_string() 
{
    Address address("2001:0DB8:AC10:FE01:0000:0000:0000:0000");
    Address expected(0x2001, 0x0DB8, 0xAC10, 0xFE01, 0x0000, 0x0000, 0x0000, 0x0000);
    
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

void test_address_from_partial_string()
{
    //Address address = "2001:0DB8:AC10:FE01::FFFF";
}

void test_address_from_partial_words()
{
    //Address address = "2001:DB8:AC10:FE01:0000:0000:0000:0000";
}

void test_address_from_malformed_string()
{
    //2001:0DB8:AC10:FE01:0000:0000:0000:ZZZZ
}

void test_address_from_incomplete_string()
{
    //Address address = "2001:0DB8:AC10:FE01";
}

void test_address_from_oversized_string()
{
    //Address address = "2001:0DB8:AC10:FE01:0000:0000:0000:0000:FFFF";
}

int main() 
{
    cout << "%SUITE_STARTING% ipv6_address_construction_test" << endl;
    cout << "%SUITE_STARTED%" << endl;

    cout << "%TEST_STARTED% test_address_from_full_string (ipv6_address_test)" << endl;
    test_address_from_full_string();
    cout << "%TEST_FINISHED% time=0 test_address_from_full_string (ipv6_address_test)" << endl;

    cout << "%SUITE_FINISHED% time=0" << endl;
    return 0;
}
