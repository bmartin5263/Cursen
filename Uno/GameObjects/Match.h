//
// Created by Brandon Martin on 7/5/19.
//

#ifndef CURSEN_MATCH_H
#define CURSEN_MATCH_H


#include <vector>
#include "Lobby.h"
#include "Deck.h"
#include "ClientMatch.h"

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
    Player& getPlayer(int player_index);

    std::string getCurrentPlayerName();

    int getNumPlayers();
    int getMyId();
    int getId(int player_index);
    int getIndex(int player_id);

    bool canDrawCard(int player_id);
    void drawCardByIndex(int player_index);

    bool canPlayCard(int player_index, int card_index);
    void playCard(int player_index, int card_index);

    bool isWaitingForWildColor();
    void setWildColor(CardColor color);

    bool aiTurn();
    bool myTurn();

    // New interface
    Card peekCardFromDeck();
    void popCardFromDeck();
    Card getCardFromPlayer(int index, int card_index);
    void removeCardFromPlayer(int index, int card_index);
    void pushCardToPile(Card card);
    bool currentPlayerHasEmptyHand();
    bool pileIsEmpty();
    int getCurrentTurn();
    int getCurrentTurnId();
    int advanceTurn();
    int getMyIndex();
    Player& getCurrentPlayer();

    bool hasId(int player_id);

    ClientMatch convertToClientMatch(int client_id);
    void readFromClientMatch(ClientMatch clientMatch);

private:

    Player players[Lobby::MAX_PLAYERS];
    Deck deck;
    Deck pile;
    int num_players;
    int current_player_index;
    int current_player_id;
    int my_id;
    bool waitingForWildCardColor;
    bool reversed;
};


#endif //CURSEN_MATCH_H
