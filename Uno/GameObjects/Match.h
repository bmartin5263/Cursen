//
// Created by Brandon Martin on 7/5/19.
//

#ifndef CURSEN_MATCH_H
#define CURSEN_MATCH_H


#include <vector>
#include "Lobby.h"
#include "Deck.h"

class Match
{

public:

    Match(Player* players, int num_players, int my_id);

    Deck& getDeck();
    Deck& getPile();
    size_t getDeckSize();
    Player* getPlayers();
    Player& getMyPlayer();
    Player& getPlayerById(int player_id);

    std::string getCurrentPlayerName();

    int getNumPlayers();
    int getMyId();
    int getId(int player_index);
    int getIndex(int player_id);
    int currentTurnId();

    bool canDrawCard(int player_id);
    void drawCard(int player_id);
    void drawCardByIndex(int player_index);

    bool canPlayCard(int player_id, int card_index);
    void playCard(int player_id, int card_index);

    bool isWaitingForWildColor();
    void setWildColor(CardColor color);

private:

    Player players[Lobby::MAX_PLAYERS];
    Deck deck;
    Deck pile;
    int num_players;
    int current_player_index;
    int current_player_id;
    int my_id;
    bool waitingForWildCardColor;
};


#endif //CURSEN_MATCH_H
