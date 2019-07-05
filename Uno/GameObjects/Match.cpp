//
// Created by Brandon Martin on 7/5/19.
//

#include "Match.h"

Match::Match(Player* players, int numPlayers) :
    num_players(numPlayers), current_player_id(-1), current_player_index(-1)
{
    for (int i = 0; i < num_players; ++i)
    {
        this->players[i] = players[i];
    }
    current_player_index = rand() % num_players;
    current_player_id = players[current_player_index].getId();
}
