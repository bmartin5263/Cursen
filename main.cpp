#include <iostream>
#include <fstream>
#include <string>
#include "Engine.h"
#include "SFML/Network.hpp"

int main() {
    //Engine::Run();
    sf::TcpSocket socket;
    auto x = socket.connect("127.0.0.1", 55001);
    std::cout << "Connected";
    std::string message = "Hi, I am a client";
    socket.send(message.c_str(), message.size());
    return 0;
}