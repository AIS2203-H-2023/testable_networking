
#ifndef TESTABLE_NETWORKING_TCP_SERVER_HPP
#define TESTABLE_NETWORKING_TCP_SERVER_HPP

#include <atomic>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include "network_helper.hpp"
#include "server/socket_handler.hpp"

#include <boost/asio.hpp>

using namespace boost::asio;
using namespace boost::asio::ip;

class tcp_server {

public:
    explicit tcp_server(int port, std::unique_ptr<message_handler> handler)
        : port_(port),
          handler_(std::move(handler)),
          acceptor_(io_service_, tcp::endpoint(tcp::v4(), port)) {}

    void start() {
        std::cout << "Serving TCP connections on port " << port_ << std::endl;

        t_ = std::thread([&] {
            std::vector<std::unique_ptr<connection>> handlers;
            try {
                while (!stop_) {
                    auto socket = std::make_unique<tcp::socket>(io_service_);
                    acceptor_.accept(*socket);// blocking operation

                    handlers.emplace_back(std::make_unique<connection>(std::move(socket), handler_.get()));
                    handlers.back()->run_handler();
                }
            } catch (const std::exception &ex) {
                std::cerr << ex.what() << std::endl;
            }
        });
    }

    void stop() {
        stop_ = true;
        acceptor_.close();
        if (t_.joinable()) t_.join();
    }

    ~tcp_server() {
        stop();
    }

private:
    int port_;
    io_service io_service_;
    tcp::acceptor acceptor_;
    std::unique_ptr<message_handler> handler_;

    std::thread t_;

    bool stop_{false};
};

#endif//TESTABLE_NETWORKING_TCP_SERVER_HPP
