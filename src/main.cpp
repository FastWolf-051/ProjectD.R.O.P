#include "server/Config/Parser/ConfigParser.h"
#include "server/Networking/Gateway/TCPGateway.h"

int main() {
    ServerConfig::Load();

    TCPGateway gateway;
    gateway.Run();

    return 0;
}