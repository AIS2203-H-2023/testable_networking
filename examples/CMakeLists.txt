
add_executable(tcp_client tcp_client.cpp)
target_link_libraries(tcp_client PRIVATE Boost::system)
target_include_directories(tcp_client PRIVATE "${CMAKE_SOURCE_DIR}/include")

add_executable(tcp_server tcp_server.cpp)
target_link_libraries(tcp_server PRIVATE Boost::system)
target_include_directories(tcp_server PRIVATE "${CMAKE_SOURCE_DIR}/include")
