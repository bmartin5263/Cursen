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

    Lobby(LobbyType type);

    void addPlayer(const Player& player);
    void removePlayer(const int& index);
    Player& getPlayer(const int& index);
    unsigned long getPlayersSize();

    LobbyType getType();

private:

    std::vector<Player> players;
    LobbyType lobbyType;

};


#endif //CURSEN_LOBBY_H
