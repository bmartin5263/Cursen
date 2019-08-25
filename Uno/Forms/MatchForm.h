//
// Created by Brandon Martin on 6/30/19.
//

#ifndef CURSEN_MATCHFORM_H
#define CURSEN_MATCHFORM_H

#include <Uno/Components/HandCard.h>
#include <Uno/Components/PlayerTile.h>
#include <Uno/GameObjects/LobbyType.h>
#include <Uno/Components/GiantCard.h>
#include <Uno/Other/DealCardsEventAnimation.h>
#include <Uno/Other/PlaceCardAnimation.h>
#include <Uno/GameObjects/ClientMatch.h>
#include <Uno/GameObjects/Match.h>
#include <Uno/Other/SkipAnimation.h>
#include <Uno/Other/ReverseAnimation.h>
#include "Cursen/Components/Form.h"
#include "Cursen/Components/Label.h"
#include "Cursen/Components/HorizontalLine.h"
#include "Uno/Components/UnoConsole.h"
#include "Uno/Components/LowerBorder.h"
#include "Uno/Components/DeckMeter.h"
#include "Uno/Components/HandMeter.h"
#include "Cursen/Cursor/Cursor.h"

#include <array>
#include <Uno/Other/WinnerAnimation.h>
#include <Uno/Other/PointTallyAnimation.h>

class MatchController;
class MatchInputState;
class MatchForm : public cursen::Form
{

public:

    MatchForm(LobbyType type, Match match);
    ~MatchForm();

    void initialize() override;
    void start();
    void exit(std::string message, bool kicked);

    void updatePlayers();
    void setDeckMeterCount(size_t size);
    void setDeckMeterSize(size_t size);
    void setHandName(std::string name);
    void updateHand(int player_index, size_t max = 14);

    void setConsoleMessage(std::string msg);
    void setConsoleWarning(std::string msg);

    void setState(const MatchInputState* state);
    void drawCardByIndex(int index);
    void effectDealCard(int index, size_t count, size_t deck_size);
    void drawCard(int index, Card drawn_card);
    void playCard(int index, int card_index, Card played_card);
    void passTurn(CardColor new_color);
    void wildColorChange(CardColor color);

    void dealInitialCards();
    void dealCards();
    void beginGame(Card initial_card);
    void waitToBegin();
    void runWinnerAnimation(int winner);
    void tallyPoints(int winner);

    void advanceTurn(int amount = 1);
    void interpretCard();

    Match& getMatch();
    MatchController* getController();
    const MatchInputState* getState();
    void updateMatch(ClientMatch clientMatch);

    void clickCard();
    void pressDraw();

    void enterPress(EVENT_ARG);
    void arrowPress(EVENT_ARG);
    void keyPress(EVENT_ARG);

    int getSelectedCardIndex();

    void displayDrawMessage(int force_draws);
    void displayTurnMessage();

    GiantCard& getFrontCard();
    PlayerTile& getPlayerTile(int index);
    UnoConsole& getConsole();

private:

    MatchController* controller;
    const MatchInputState* state;
    Match match;

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
    std::vector<HandCard*> wild_cards;

    DealCardsEventAnimation dealCardsEventController;
    PlaceCardAnimation placeCardAnimation;
    SkipAnimation skip_animation;
    ReverseAnimation reverse_animation;
    WinnerAnimation winner_animation;
    PointTallyAnimation point_tally_animation;
    cursen::Animation wildColorAnimation;
    cursen::Animation wild_hand_cards_animation;

    cursen::AlarmHandle ai_handle;
};


#endif //CURSEN_MATCHFORM_H
