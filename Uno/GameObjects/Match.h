//
// Created by Brandon Martin on 7/5/19.
//

#ifndef CURSEN_MATCH_H
#define CURSEN_MATCH_H


#include <vector>
#include "Lobby.h"
#include "Deck.h"
#include "ClientMatch.h"

class Match : public Serializable
{

public:

    static int CalculateNextTurn(int current_turn, int num_players, bool reversed);

    Match() = default;
    Match(Player* players, int num_players, int my_id);
    Match& operator=(const Match& other);

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

    bool canPass(int player_index);
    void pass();
    int getConsecutivePasses();

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
    int peekNextTurn();
    int getMyIndex();
    Player& getCurrentPlayer();
    int getForceDrawAmount();
    bool isSkipCard();
    bool isReverseCard();
    bool isTurnOrderReversed();
    void reverseTurnOrder();

    bool hasId(int player_id);

    ClientMatch convertToClientMatch(int client_id);
    void readFromClientMatch(ClientMatch clientMatch);
    size_t serialize(char* const buffer) const override;
    size_t deserialize(const char* const buffer) override;
    size_t sizeOf() const override;

private:

    Player players[Lobby::MAX_PLAYERS];
    Deck deck;
    Deck pile;
    int num_players;
    int current_player_index;
    int current_player_id;
    int my_id;
    int consecutive_passes;
    bool waitingForWildCardColor;
    bool reversed;
};


#endif //CURSEN_MATCH_H
