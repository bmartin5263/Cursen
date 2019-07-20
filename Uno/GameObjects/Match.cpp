//
// Created by Brandon Martin on 7/5/19.
//

#include <cassert>
#include "Match.h"

Match::Match(Player* players, int numPlayers, int my_id) :
    num_players(numPlayers), current_player_id(players[0].getId()), current_player_index(0), my_id(my_id)
{
    for (int i = 0; i < num_players; ++i)
    {
        this->players[i] = players[i];
    }
    current_player_index = rand() % num_players;
    current_player_id = players[current_player_index].getId();
}

Deck& Match::getDeck()
{
    return deck;
}

Player* Match::getPlayers()
{
    return players;
}

int Match::getNumPlayers()
{
    return num_players;
}

size_t Match::getDeckSize()
{
    return deck.size();
}

int Match::getMyId()
{
    return my_id;
}

Player& Match::getMyPlayer()
{
    for (int i = 0; i < num_players; ++i)
    {
        if (players->getId() == my_id) return players[i];
    }
    assert(false);
    return players[0];
}

bool Match::canDrawCard(int player_id)
{
    return current_player_id == player_id && deck.size() > 0;
}

void Match::drawCard(int player_id)
{
    assert(canDrawCard(player_id));
    Card c = deck.popCard();
    getPlayerById(player_id).getHand().add(c);
}

Player& Match::getPlayerById(int player_id)
{
    for (auto& player : players)
    {
        if (player.getId() == player_id) return player;
    }
    assert(false);
    return players[0];
}

void Match::drawCardByIndex(int player_index)
{
    Card c = deck.popCard();
    players[player_index].getHand().add(c);
}

std::string Match::getCurrentPlayerName()
{
    return players[current_player_index].getName();
}
