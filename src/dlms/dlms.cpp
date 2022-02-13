//
// Created by andrew on 2022/2/13.
//
#include <iostream>
#include ""

#include "dlms.h"

int main(int argc, char* argv[]) {



// Initialize Google's logging library.
    google::InitGoogleLogging(argv[0]);

    // Optional: parse command line flags
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    LOG(INFO) << "Hello, world!";

    // glog/stl_logging.h allows logging STL containers.
    std::vector<int> x;
    x.push_back(1);
    x.push_back(2);
    x.push_back(3);
    LOG(INFO) << "ABC, it's easy as " << x;



    std::cout << "=====" << std::endl;



    return 0;
}




