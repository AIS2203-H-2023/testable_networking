
#include "server/tcp_server.hpp"
#include <sstream>

struct my_handler : message_handler {

    std::string handle_message(const std::string &message) override {
        std::stringstream ss;
        ss << "Hello, " << message << "!\n";
        return ss.str();
    }
};

int main(int argc, char **argv) {

    int port = 9090;
    if (argc == 2) {
        // assuming <port> as input
        try {
            port = std::stoi(argv[1]);
        } catch (const std::exception &ex) {
            std::cerr << "Unable to parse port.." << std::endl;
            return 1;
        }
    }

    try {
        my_handler handler;

        tcp_server server(port, &handler);
        server.start();

        std::cout << "Press a key to continue..." << std::endl;
        while (std::cin.get() != '\n') {}

        server.stop();

    } catch (const std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }
}
