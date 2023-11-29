//
// Created by pepos on 11/28/2023.
//
#include <iostream>
#include "../Tnet/Tnet.h"
int main() {
    if (Tnet::Network::Initialize()) {
        std::cout << "Server Initialized\n";

        Tnet::Socket socket;
        if (socket.Create() == Tnet::TResults::T_Success) {
            std::cout << "Connection Created Succesfully\n";
            if (socket.Listen(Tnet::IPEndpoint("0.0.0.0", 1996)) == Tnet::TResults::T_Success) {
                std::cout << "Socket Successfully Listening to 1996\n";
                Tnet::Socket clientConnection;
                if (socket.Accept(clientConnection) == Tnet::TResults::T_Success) {
                    std::cout << "Socket Successfully Connected\n";
                }
                socket.Close();
            } else {
                std::cout << "Socket failed to  create\n";
            }
        Tnet::Network::Shutdown();
    }
}

    return 0;
}

