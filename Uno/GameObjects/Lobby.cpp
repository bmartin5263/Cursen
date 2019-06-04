//
// Created by Brandon Martin on 4/11/19.
//

#include "Lobby.h"
#include "../Constants.h"

Lobby::Lobby() :
    numPlayers(0), searching(false)
{
    for (int i = 0; i < MAX_PLAYERS; i++) {
        players[i] = nullptr;
    }
    for (int i = 0; i < MAX_CHAT; i++) {
        messages[i] = "";
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

PlayerColor Lobby::getAvailableColor() const {
    static int i = 0;

    int start = i;
    while (true) {
        PlayerColor color = Constants::COLORS[i];
        i = (i + 1) % Constants::NUM_COLORS;
        bool ok = true;
        for (int j = 0; j < numPlayers; j++) {
            if (players[j]->getColor() == color) {
                ok = false;
                break;
            }
        }
        if (ok) return color;
        if (i == start) throw std::logic_error("Not enough colors");
    }
}

PlayerColor Lobby::getAvailableColorRGBY() const {
    static int i = 0;

    int num_colors_rgb = Constants::NUM_COLORS - 2;
    int start = i;
    while (true) {
        PlayerColor color = Constants::COLORS[i];
        if (!colorTaken(color)) return color;
        i = (i + 1) % num_colors_rgb;
        if (i == start) throw std::logic_error("Not enough colors");
    }
}

bool Lobby::colorTaken(PlayerColor color) const
{
    for (int j = 0; j < numPlayers; j++) {
        if (players[j]->getColor() == color) {
           return true;
        }
    }
    return false;
}
