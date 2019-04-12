//
// Created by Brandon Martin on 4/11/19.
//

#include "Lobby.h"

Lobby::Lobby(LobbyType type) :
    lobbyType(type)
{

}

void Lobby::addPlayer(const Player &player) {
    if (players.size() >= 4) {
        throw std::overflow_error("Max Players is 4");
    }
    players.push_back(player);
}

void Lobby::removePlayer(const int &index) {
    if (players.empty()) {
        throw std::underflow_error("No Players to Remove");
    }
    players.erase(players.begin() + index);
}

Player& Lobby::getPlayer(const int &index) {
    if (index < 0 || index >= players.size()) {
        throw std::range_error("Player index out of range");
    }
    return players[index];
}

unsigned long Lobby::getPlayersSize() {
    return players.size();
}

LobbyType Lobby::getType() {
    return lobbyType;
}
