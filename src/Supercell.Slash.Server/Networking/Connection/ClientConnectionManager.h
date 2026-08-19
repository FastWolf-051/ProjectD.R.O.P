#pragma once

#include <asio.hpp>
#include <thread>
#include <string>

#include "ClientConnection.h"
#include "../../../Supercell.Slash.Titan/Debug/Debugger.h"

class ClientConnectionManager {
public:
    ClientConnectionManager() {}

    void OnConnect(asio::ip::tcp::socket socket) {
        try {
            Debugger::Print("New connection from %s", socket.remote_endpoint().address().to_string().c_str());
        }
        catch (...) {
            Debugger::Print("New connection");
        }

        std::thread([socket = std::move(socket)]() mutable {
            ClientConnection connection(std::move(socket));

            try {
                connection.Run();
            }
            catch (const std::exception& exception) {
                Debugger::Error("got exception occurred while processing session: %s", exception.what());
            }
        }).detach();
    }
};