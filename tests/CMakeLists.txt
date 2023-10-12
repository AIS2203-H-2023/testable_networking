
add_executable(tcp_test tcp_test.cpp)
add_test(NAME tcp_test COMMAND tcp_test)
target_link_libraries(tcp_test PRIVATE Boost::system Catch2::Catch2WithMain)
target_include_directories(tcp_test PRIVATE "${CMAKE_SOURCE_DIR}/include")

add_executable(helper_test helper_test.cpp)
add_test(NAME helper_test COMMAND helper_test)
target_link_libraries(helper_test PRIVATE Catch2::Catch2WithMain)
target_include_directories(helper_test PRIVATE "${CMAKE_SOURCE_DIR}/include")