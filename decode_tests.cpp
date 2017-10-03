/* 
 * File:   newsimpletest.cpp
 * Author: rnetuka
 *
 * Created on 21. září 2016, 23:55
 */

#include <iostream>
#include <stdexcept>
#include <string>

#include "base64.h"

using namespace base64;
using namespace std;

const string TESTSUITE = "Decoding tests";


void test_decode_one_char()
{
    string result = decode('T', 'Q', '=', '=');
    string expected = "M";
    
    if (result != expected)
        cout << "%TEST_FAILED% time=0 testname=test_decode_one_char (" << TESTSUITE << ") message=" << "Expected: '" << expected << "' but was: '" << result <<"'" << endl;
}

void test_decode_two_chars()
{
    string result = decode('T', 'W', 'E', '=');
    string expected = "Ma";
    
    if (result != expected)
        cout << "%TEST_FAILED% time=0 testname=test_decode_two_chars (" << TESTSUITE << ") message=" << "Expected: '" << expected << "' but was: '" << result <<"'" << endl;
}

void test_decode_three_chars()
{
    string result = decode('T', 'W', 'F', 'u');
    string expected = "Man";
    
    if (result != expected)
        cout << "%TEST_FAILED% time=0 testname=test_decode_three_chars (" << TESTSUITE << ") message=" << "Expected: '" << expected << "' but was: '" << result <<"'" << endl;
}

void test_decode_invalid_chars()
{
    try
    {
        decode('T', '=', '=', '=');
    }
    catch (const invalid_argument& ex)
    {
        return;
    }
    cout << "%TEST_FAILED% time=0 testname=test_decode_invalid_chars (" << TESTSUITE << ") message=" << "Expected exception but none was thrown" << endl;
}

void test_decode_string()
{
    string result = decode("TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWF"
            "zb24sIGJ1dCBieSB0aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltY"
            "WxzLCB3aGljaCBpcyBhIGx1c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZ"
            "lcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGludWVkIGFuZCBpbmRlZmF0aWdhY"
            "mxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRoZSBzaG9ydCB2ZWh"
            "lbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=");
    
    string expected = "Man is distinguished, not only by his reason, but by this "
            "singular passion from other animals, which is a lust of the mind, "
            "that by a perseverance of delight in the continued and indefatigable "
            "generation of knowledge, exceeds the short vehemence of any carnal pleasure.";
    
    if (result != expected)
        cout << "%TEST_FAILED% time=0 testname=test_decode_string (" << TESTSUITE << ") message=" << "Expected: '" << expected << "' but was: '" << result <<"'" << endl;
    
}

int main(int argc, char** argv) 
{
    cout << "%SUITE_STARTING% " << TESTSUITE << endl;
    cout << "%SUITE_STARTED%" << endl;

    cout << "%TEST_STARTED% test_decode_one_char (" << TESTSUITE << ")" << endl;
    test_decode_one_char();
    cout << "%TEST_FINISHED% time=0 test_decode_one_char (" << TESTSUITE << ")" << endl;
    
    cout << "%TEST_STARTED% test_decode_two_chars (" << TESTSUITE << ")" << endl;
    test_decode_two_chars();
    cout << "%TEST_FINISHED% time=0 test_decode_two_chars (" << TESTSUITE << ")" << endl;
    
    cout << "%TEST_STARTED% test_decode_three_chars (" << TESTSUITE << ")" << endl;
    test_decode_three_chars();
    cout << "%TEST_FINISHED% time=0 test_decode_three_chars (" << TESTSUITE << ")" << endl;
    
    cout << "%TEST_STARTED% test_decode_invalid_chars (" << TESTSUITE << ")" << endl;
    test_decode_invalid_chars();
    cout << "%TEST_FINISHED% time=0 test_decode_invalid_chars (" << TESTSUITE << ")" << endl;
    
    cout << "%TEST_STARTED% test_decode_string (" << TESTSUITE << ")" << endl;
    test_decode_string();
    cout << "%TEST_FINISHED% time=0 test_decode_string (" << TESTSUITE << ")" << endl;

    cout << "%SUITE_FINISHED% time=0" << endl;

    return 0;
}

