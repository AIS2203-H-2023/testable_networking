
#include <catch2/catch_test_macros.hpp>

#include "server/tcp_server.hpp"

TEST_CASE("Test TCP server start/stop") {

    int port = 9090;

    for (int i = 0; i < 5; i++) {
        tcp_server server(port, nullptr);
        server.start();

        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        server.stop();
    }
}
