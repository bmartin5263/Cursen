//
// Created by Brandon Martin on 6/30/19.
//

#ifndef CURSEN_MATCHFORM_H
#define CURSEN_MATCHFORM_H

#include <Uno/UnoComponents/HandCard.h>
#include <Uno/UnoComponents/PlayerTile.h>
#include <Uno/GameObjects/LobbyType.h>
#include <Uno/UnoComponents/GiantCard.h>
#include <Uno/Other/DealCardsEventAnimation.h>
#include <Uno/Other/PlaceCardAnimation.h>
#include <Uno/GameObjects/ClientMatch.h>
#include "Cursen/Components/Form.h"
#include "Cursen/Components/Label.h"
#include "Cursen/Components/HorizontalLine.h"
#include "Uno/UnoComponents/UnoConsole.h"
#include "Uno/UnoComponents/LowerBorder.h"
#include "Uno/UnoComponents/DeckMeter.h"
#include "Uno/UnoComponents/HandMeter.h"
#include "Cursen/Cursor/Cursor.h"

class MatchController;
class Match;
class MatchState;
class MatchForm : public cursen::Form
{

public:

    MatchForm(LobbyType type, Match* match);
    ~MatchForm();

    void initialize() override;
    void start();

    void updatePlayers();
    void setDeckMeterCount(size_t size);
    void setDeckMeterSize(size_t size);
    void setHandName(std::string name);
    void updateHand(size_t max = 14);

    void setConsoleMessage(std::string msg);
    void setConsoleWarning(std::string msg);

    void setState(const MatchState* state);
    void drawCardByIndex(int index);
    void effectDealCard(int index, size_t count, size_t deck_size);
    void drawCard(int index, Card drawn_card);
    void playCard(int index, int card_index, Card played_card);
    void wildColorChange(CardColor color);

    void dealInitialCards();
    void dealCards();
    void beginGame(Card initial_card);
    void waitToBegin();

    Match* getMatch();
    MatchController* getController();
    const MatchState* getState();
    void updateMatch(ClientMatch clientMatch);

    void clickCard();
    void pressDraw();

    void enterPress(const cursen::Event& event);
    void arrowPress(const cursen::Event& event);
    void keyPress(const cursen::Event& event);

    int getSelectedCardIndex();

    GiantCard& getFrontCard();
    PlayerTile& getPlayerTile(int index);

private:

    MatchController* controller;
    Match* match;
    const MatchState* state;

    int card_index;
    int hand_index;

    cursen::Label welcome;
    cursen::Label deck_size;
    cursen::Label deck_label;
    cursen::Label hand_label;
    HandMeter handMeter;
    UnoConsole console;
    LowerBorder lowerBorder;
    cursen::Box hand_box;
    HandCard leftCard;
    HandCard rightCard;
    HandCard card_array[14];
    DeckMeter deckMeter;
    PlayerTile p0Tile;
    PlayerTile p1Tile;
    PlayerTile p2Tile;
    PlayerTile p3Tile;
    PlayerTile* tile_array[4];
    GiantCard front_card;
    GiantCard back_card;

    DealCardsEventAnimation dealCardsEventController;
    PlaceCardAnimation placeCardAnimation;
    cursen::Animation wildColorAnimation;
};


#endif //CURSEN_MATCHFORM_H
