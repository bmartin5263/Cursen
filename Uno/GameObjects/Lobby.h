//
// Created by Brandon Martin on 4/11/19.
//

#ifndef CURSEN_LOBBY_H
#define CURSEN_LOBBY_H


#include <vector>
#include "LobbyType.h"
#include "Player.h"

class Lobby {

public:

    static const int MAX_PLAYERS = 4;
    static const int MIN_PLAYERS_TO_START = 2;

    Lobby(LobbyType type);

    void addPlayer(Player * const player);
    void removePlayer(const int& index);
    Player* getPlayer(const int& index);
    int getNumPlayers();

    void startSearch();
    void stopSearch();
    bool isSearching();

    LobbyType getType();

private:

    Player* players[MAX_PLAYERS];
    int numPlayers;
    LobbyType lobbyType;
    bool searching;

};


#endif //CURSEN_LOBBY_H
