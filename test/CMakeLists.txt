



add_executable(gmock_test gmock_test.cpp)
target_link_libraries(gmock_test
        PUBLIC gtest
        PUBLIC gmock
        PUBLIC pthread
        )

