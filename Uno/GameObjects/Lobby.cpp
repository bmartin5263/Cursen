//
// Created by Brandon Martin on 4/11/19.
//

#include "Lobby.h"

Lobby::Lobby(LobbyType type) :
    lobbyType(type), numPlayers(0), searching(false)
{
    for (int i = 0; i < MAX_PLAYERS; i++) {
        players[i] = nullptr;
    }
}

void Lobby::addPlayer(Player * const player) {
    if (numPlayers >= MAX_PLAYERS) {
        throw std::overflow_error("Max Players Reached");
    }
    players[numPlayers++] = player;
}

void Lobby::removePlayer(const int &index) {
    if (numPlayers <= 0) {
        throw std::underflow_error("No Players to Remove");
    }
    delete players[index];
    players[index] = nullptr;
    numPlayers--;

    for (int i = index + 1; i < MAX_PLAYERS; i++) {
        players[i-1] = players[i];
        players[i] = nullptr;
    }
}

Player* Lobby::getPlayer(const int &index) const {
    if (index < 0 || index >= numPlayers) {
        throw std::range_error("Player index out of range");
    }
    return players[index];
}

int Lobby::getNumPlayers() const {
    return numPlayers;
}

LobbyType Lobby::getType() const {
    return lobbyType;
}

void Lobby::startSearch() {
    searching = true;
}

void Lobby::stopSearch() {
    searching = false;
}

bool Lobby::isSearching() const {
    return searching;
}

Lobby::~Lobby() {
    while (numPlayers > 0) {
        removePlayer(numPlayers - 1);
    }
}