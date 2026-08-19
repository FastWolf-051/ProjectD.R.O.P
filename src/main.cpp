#include "Supercell.Slash.Server/Config/Parser/ConfigParser.h"
#include "Supercell.Slash.Server/Networking/Gateway/TCPGateway.h"

int main() {
    ServerConfig::Load();

    TCPGateway gateway;
    gateway.Run();

    return 0;
}