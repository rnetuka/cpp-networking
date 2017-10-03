/* 
 * File:   base64_test.cpp
 * Author: rnetuka
 *
 * Created on 14. září 2016, 18:15
 */

#include <iostream>
#include <stdexcept>
#include <string>

#include "base64.h"

using namespace base64;
using namespace std;


const string TESTSUITE = "Encoding tests";


void test_encode_three_chars() 
{
    string result = encode('M', 'a', 'n');
    string expected = "TWFu";
    
    if (result != expected) 
        cout << "%TEST_FAILED% time=0 testname=test_encode_three_chars (" << TESTSUITE << ") message=" << "Expected: '" << expected << "' but was: '" << result <<"'" << endl;
}

void test_encode_two_chars() 
{
    string result = encode('M', 'a');
    string expected = "TWE=";
    
    if (result != expected) 
        cout << "%TEST_FAILED% time=0 testname=test_encode_two_chars (" << TESTSUITE << ") message=" << "Expected: '" << expected << "' but was: '" << result <<"'" << endl;
}

void test_encode_one_char()
{
    string result = encode('M');
    string expected = "TQ==";
    
    if (result != expected) 
        cout << "%TEST_FAILED% time=0 testname=test_encode_one_char (" << TESTSUITE << ") message=" << "Expected: '" << expected << "' but was: '" << result <<"'" << endl;
}

void test_encode_string() 
{
    string result = encode("Man is distinguished, not only by his reason, but by this "
            "singular passion from other animals, which is a lust of the mind, "
            "that by a perseverance of delight in the continued and indefatigable "
            "generation of knowledge, exceeds the short vehemence of any carnal pleasure.");
    
    string expected = "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWF"
            "zb24sIGJ1dCBieSB0aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltY"
            "WxzLCB3aGljaCBpcyBhIGx1c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZ"
            "lcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGludWVkIGFuZCBpbmRlZmF0aWdhY"
            "mxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRoZSBzaG9ydCB2ZWh"
            "lbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=";
    
    if (result != expected) 
        cout << "%TEST_FAILED% time=0 testname=test_encode_string (" << TESTSUITE << ") message=" << "Expected: '" << expected << "' but was: '" << result <<"'" << endl;
}

int main(int argc, char** argv) 
{
    cout << "%SUITE_STARTING% " << TESTSUITE << endl;
    cout << "%SUITE_STARTED%" << endl;

    cout << "%TEST_STARTED% test_encode_three_chars (" << TESTSUITE << ")" << endl;
    test_encode_three_chars();
    cout << "%TEST_FINISHED% time=0 test_encode_three_chars (" << TESTSUITE << ")" << endl;
    
    cout << "%TEST_STARTED% test_encode_two_chars (" << TESTSUITE << ")" << endl;
    test_encode_two_chars();
    cout << "%TEST_FINISHED% time=0 test_encode_two_chars (" << TESTSUITE << ")" << endl;
    
    cout << "%TEST_STARTED% test_encode_one_char (" << TESTSUITE << ")" << endl;
    test_encode_one_char();
    cout << "%TEST_FINISHED% time=0 test_encode_one_char (" << TESTSUITE << ")" << endl;

    cout << "%TEST_STARTED% test_encode_string (" << TESTSUITE << ")" << endl;
    test_encode_string();
    cout << "%TEST_FINISHED% time=0 test_encode_string (" << TESTSUITE << ")" << endl;

    cout << "%SUITE_FINISHED% time=0" << endl;

    return 0;
}