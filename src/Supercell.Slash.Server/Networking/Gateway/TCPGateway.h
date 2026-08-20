#pragma once

#include <asio.hpp>
#include <string>

#include "../../Config/Parser/ConfigParser.h"
#include "../../../Supercell.Slash.Server/Networking/Connection/ClientConnectionManager.h"
#include "../../../Supercell.Slash.Titan/Debug/Debugger.h"

class TCPGateway {
private:
    static const int MAX_CURRENT_CONNECTION_COUNT = 10;

    asio::io_context _ioContext;
    asio::ip::tcp::acceptor _acceptor;

    ClientConnectionManager* _manager;

    std::string _address;
    int _port;

public:
    TCPGateway() : _acceptor(_ioContext) {
        _manager = new ClientConnectionManager();

        const char* address = ServerConfig::GetString("SERVER_IP");

        _address = address != nullptr ? address : "0.0.0.0";

        _port = ServerConfig::GetInt("SERVER_PORT");
    }

    ~TCPGateway() {
        Stop();

        delete _manager;
    }

    void Start() {
        asio::ip::address address = asio::ip::make_address(_address);

        asio::ip::tcp::endpoint endpoint(address, static_cast<unsigned short>(_port));

        asio::error_code error;

        _acceptor.open(endpoint.protocol(), error);

        _acceptor.set_option(asio::ip::tcp::acceptor::reuse_address(true));
        _acceptor.bind(endpoint, error);
        _acceptor.listen(MAX_CURRENT_CONNECTION_COUNT, error);

        if (error) {
            throw asio::system_error(error);
        }

        Debugger::Print("Server is listening on %s:%d", _address.c_str(), _port);
    }

    void Run() {
        Start();

        while (_acceptor.is_open()) {
            asio::error_code error;

            asio::ip::tcp::socket socket(_ioContext);

            _acceptor.accept(socket, error);

            if (error) {
                if (error == asio::error::eof) {
                    Debugger::Print("[ClientConnection] Client disconnected");
                    break;
                }

                Debugger::Error("[ClientConnection] Receive failed: %s", error.message().c_str());

                break;
            }

            _manager->OnConnect(std::move(socket));
        }
    }

    void Stop() {
        asio::error_code error;

        _acceptor.close(error);

        _ioContext.stop();
    }
};