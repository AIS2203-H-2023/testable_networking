
#include <catch2/catch_test_macros.hpp>

#include "server/tcp_server.hpp"

TEST_CASE("Test TCP server start/stop") {

    int port = 9090;

    for (int i = 0; i < 2; i++) {
        tcp_server server(port);
        server.start();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        server.stop();
    }

}

