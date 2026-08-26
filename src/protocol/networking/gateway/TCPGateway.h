#pragma once

#include <asio.hpp>
#include <string>

#include "../../../config/parser/ConfigParser.h"
#include "../../../protocol/networking/session/ClientSessionHandler.h"
#include "../../../shared/utils/debug/Debugger.h"

class TCPGateway {
private:
    static const int MAX_CONNECTIONS_AT_ONCE = 10;

    asio::io_context _ioContext;
    asio::ip::tcp::acceptor _acceptor;

    ClientSessionHandler* _manager;

    std::string _address;
    int _port;

public:
    TCPGateway() : _acceptor(_ioContext) {
        _manager = new ClientSessionHandler();

        const char* address = ServerConfig::GetString("SERVER_IP");

        _address = address != nullptr ? address : "0.0.0.0";

        _port = ServerConfig::GetInt("SERVER_PORT");
    }

    void Start() {
        asio::ip::address address = asio::ip::make_address(_address);

        asio::ip::tcp::endpoint endpoint(address, static_cast<unsigned short>(_port));

        asio::error_code error;

        _acceptor.open(endpoint.protocol(), error);

        _acceptor.set_option(asio::ip::tcp::acceptor::reuse_address(true));
        _acceptor.bind(endpoint, error);
        _acceptor.listen(MAX_CONNECTIONS_AT_ONCE, error);

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
                    Debugger::Print("[TCPGateway]: client disconnected");
                    break;
                }

                Debugger::Error("[TCPGateway]: receiving data failed: %s", error.message().c_str());

                break;
            }

            _manager->OnNewSession(std::move(socket));
        }
    }

    void Stop() {
        asio::error_code error;

        _acceptor.close(error);

        _ioContext.stop();
    }

    ~TCPGateway() {
        Stop();

        delete _manager;
    }
};