/* 
 * File:   ipv4_checksum_test.cpp
 * Author: rnetuka
 *
 * Created on 26. září 2016, 16:15
 */

#include "ipv4.h"

#include <iostream>

using namespace std;
using namespace ipv4;


void test_checksum() 
{
    cout << "ipv4_checksum_test test 1" << endl;
    /*Header header;
    header.set_total_length(48);
    header.set_identification(17442);
    header.set_dont_fragment();
    header.set_time_to_live(128);
    header.set_data_protocol(6);
    header.set_source_ip_address("140.124.25.172");
    header.set_destination_ip_address("174.36.30.43");
    
    int expected = 17454;
    int result = checksum(header);
    
    if (result != expected)
        cout << "%TEST_FAILED% time=0 testname=test_checksum (ipv4_checksum_test) message=Expected: " << expected << " but got " << result << endl;*/
}

void test_checksum2() 
{
    std::cout << "ipv4_checksum_test test 2" << std::endl;
    std::cout << "%TEST_FAILED% time=0 testname=test2 (ipv4_checksum_test) message=error message sample" << std::endl;
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% ipv4_checksum_test" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test_checksum (ipv4_checksum_test)" << std::endl;
    test_checksum();
    std::cout << "%TEST_FINISHED% time=0 test_checksum (ipv4_checksum_test)" << std::endl;

    std::cout << "%TEST_STARTED% test2 (ipv4_checksum_test)\n" << std::endl;
    test_checksum2();
    std::cout << "%TEST_FINISHED% time=0 test2 (ipv4_checksum_test)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return 0;
}

