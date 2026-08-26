#pragma once

#include <asio.hpp>
#include <thread>
#include <string>

#include "ClientSession.h"
#include "../../../shared/utils/debug/Debugger.h"

class ClientSessionHandler {
public:
    ClientSessionHandler() {}

    void OnNewSession(asio::ip::tcp::socket socket) {
        Debugger::Print("New connection from %s", socket.remote_endpoint().address().to_string().c_str());

        std::thread([socket = std::move(socket)]() mutable {
            ClientSession session(std::move(socket));

            try {
                session.Run();
            }
            catch (const std::exception& exception) {
                Debugger::Error("caught exception while processing session: %s", exception.what());
            }
        }).detach();
    }
};