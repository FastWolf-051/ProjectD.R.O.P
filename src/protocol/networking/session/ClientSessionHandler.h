#pragma once

#include <asio.hpp>
#include <thread>
#include <string>

#include "ClientSession.h"
#include "../../../shared/utils/debug/Debugger.h"

class ClientSessionHandler {
public:
    ClientSessionHandler() {}

    void OnConnect(asio::ip::tcp::socket socket) {
        try {
            Debugger::Print("New connection from %s", socket.remote_endpoint().address().to_string().c_str());
        }
        catch (...) {
            Debugger::Print("New connection");
        }

        std::thread([socket = std::move(socket)]() mutable {
            ClientSession session(std::move(socket));

            try {
                session.Run();
            }
            catch (const std::exception& exception) {
                Debugger::Error("got exception occurred while processing session: %s", exception.what());
            }
        }).detach();
    }
};