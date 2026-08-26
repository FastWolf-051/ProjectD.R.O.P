#include "config/parser/ConfigParser.h"
#include "protocol/networking/gateway/TCPGateway.h"

int main() {
    ServerConfig::Load();

    TCPGateway gateway;
    gateway.Run();

    return 0;
}