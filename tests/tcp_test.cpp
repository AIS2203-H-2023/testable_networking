
#include <catch2/catch_test_macros.hpp>

#include "client/tcp_client.hpp"
#include "server/tcp_server.hpp"

namespace {

    const int port = 9090;

    struct my_message_handler : message_handler {

        my_message_handler(const std::function<std::string(const std::string &)> &f) : f_(f) {}

        std::string handle_message(const std::string &message) override {
            return f_(message);
        }

    private:
        std::function<std::string(const std::string &)> f_;
    };
}// namespace

TEST_CASE("Test TCP server start/stop") {

    for (int i = 0; i < 5; i++) {
        tcp_server server(port, nullptr);
        server.start();

        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        server.stop();
    }
}

TEST_CASE("Test socket communication") {

    auto msgGenerator = [](auto msg) {
        return "Hello, " + msg + "!";
    };

    my_message_handler handler(msgGenerator);

    tcp_server server(port, &handler);
    server.start();

    tcp_client client("127.0.0.1", port);
    std::string msg{"Nils"};
    client.send(msg);

    auto expected = msgGenerator(msg);
    auto actual = client.recv();

    CHECK(expected == actual);
}
