//
// Created by Brandon Martin on 6/30/19.
//

#include <cassert>

#include <Uno/Match/MatchControllers.h>
#include <Uno/Data/DataManager.h>
#include "MatchForm.h"
#include "Cursen/CursenApplication.h"
#include "Uno/Match/FSM/MatchState.h"
#include "Uno/Match/FSM/MatchFSM.h"
#include "Uno/GameObjects/Match.h"

using namespace cursen;

MatchForm::MatchForm(LobbyType type, Match* match) :
        Form(cursen::Vect2(70, 33)), match(match), card_index(0), hand_index(0)
{
    switch (type)
    {
        case LobbyType::LOCAL:
            controller = &MatchControllers::matchLocalController;
            break;
        case LobbyType::HOST:
            controller = &MatchControllers::matchHostController;
            break;
        case LobbyType::JOIN:
            controller = &MatchControllers::matchClientController;
            break;
    }
    controller->setMatchForm(this);
}

MatchForm::~MatchForm()
{
    delete match;
}

void MatchForm::initialize()
{
    DataManager::SetContext(Context::ContextMatch);
    welcome.initialize();
    welcome.setPosition(Vect2(0,0));
    welcome.setText("Welcome to the Match!");
    welcome.onEscapePress([](const Event e) { CursenApplication::CloseForm(); });
    welcome.onDeletePress([&](const Event e) {
        front_card.shrink();
    });

    console.initialize();
    console.setText("Welcome!");

    lowerBorder.initialize();
    lowerBorder.setPosition(Vect2(0, 6));

    deck_label.initialize();
    deck_label.setPosition(Vect2(1, 8));
    deck_label.setText("Deck:");

    hand_label.initialize();
    hand_label.setPosition(Vect2(1, 24));
    setHandName("Unknown");

    handMeter.initialize();
    handMeter.setPosition(Vect2(55, 24));

    deck_size.initialize();
    deck_size.setPosition(Vect2(1, 9));
    deck_size.setText("0 Cards");

    hand_box.initialize();
    hand_box.setPosition(Vect2(0, 23));
    hand_box.setSize(Vect2(70, 3));
    hand_box.setUpperRight(CursesManager::RTEE);
    hand_box.setLowerRight(CursesManager::RTEE);
    hand_box.setLowerLeft(CursesManager::LTEE);
    hand_box.setUpperLeft(CursesManager::LTEE);
    hand_box.setFill(Content::TRANSPARENT);
    hand_box.setDrawOrder(lowerBorder.getDrawOrder() + 1);

    deckMeter.initialize();
    deckMeter.setPosition(Vect2(1, 11));

    p0Tile.initialize();
    p0Tile.setPosition(Vect2(55, 7));

    p1Tile.initialize();
    p1Tile.setPosition(Vect2(55, 11));

    p2Tile.initialize();
    p2Tile.setPosition(Vect2(55, 15));

    p3Tile.initialize();
    p3Tile.setPosition(Vect2(55, 19));

    leftCard.initialize();
    leftCard.setPosition(Vect2(2, 27));
    leftCard.setLeft();

    rightCard.initialize();
    rightCard.setPosition(Vect2(64, 27));
    rightCard.setRight();

    int x = 7;
    for (int i = 0; i < 14; i++)
    {
        card_array[i].initialize();
        card_array[i].setPosition(Vect2(x + (4 * i), 27));
        card_array[i].setHidden(true);
        card_array[i].onClick(std::bind(&MatchForm::clickCard, this));
    }

    //back_card.initialize();
    back_card.initialize();
    back_card.setPosition(Vect2(27,8));
    back_card.setHidden(true);

    front_card.initialize();
    front_card.setPosition(Vect2(29,10));
    front_card.drawOnTopOf(back_card);
    front_card.setHidden(true);

//    card_cursor.moveTo(&card_array[0]);
//    card_cursor.mapComponent(&card_array[0], ArrowMap(&card_array[13], nullptr, &card_array[1], nullptr));
//    card_cursor.mapComponent(&card_array[1], ArrowMap(&card_array[0], nullptr, &card_array[2], nullptr));
//    card_cursor.mapComponent(&card_array[2], ArrowMap(&card_array[1], nullptr, &card_array[3], nullptr));
//    card_cursor.mapComponent(&card_array[3], ArrowMap(&card_array[2], nullptr, &card_array[4], nullptr));
//    card_cursor.mapComponent(&card_array[4], ArrowMap(&card_array[3], nullptr, &card_array[5], nullptr));
//    card_cursor.mapComponent(&card_array[5], ArrowMap(&card_array[4], nullptr, &card_array[6], nullptr));
//    card_cursor.mapComponent(&card_array[6], ArrowMap(&card_array[5], nullptr, &card_array[7], nullptr));
//    card_cursor.mapComponent(&card_array[7], ArrowMap(&card_array[6], nullptr, &card_array[8], nullptr));
//    card_cursor.mapComponent(&card_array[8], ArrowMap(&card_array[7], nullptr, &card_array[9], nullptr));
//    card_cursor.mapComponent(&card_array[9], ArrowMap(&card_array[8], nullptr, &card_array[10], nullptr));
//    card_cursor.mapComponent(&card_array[10], ArrowMap(&card_array[9], nullptr, &card_array[11], nullptr));
//    card_cursor.mapComponent(&card_array[11], ArrowMap(&card_array[10], nullptr, &card_array[12], nullptr));
//    card_cursor.mapComponent(&card_array[12], ArrowMap(&card_array[11], nullptr, &card_array[13], nullptr));
//    card_cursor.mapComponent(&card_array[13], ArrowMap(&card_array[12], nullptr, &card_array[0], nullptr));
//    card_cursor.setEnabled(true);

    tile_array[0] = &p0Tile;
    tile_array[1] = &p1Tile;
    tile_array[2] = &p2Tile;
    tile_array[3] = &p3Tile;

    start();

    onEnterPress(std::bind(&MatchForm::enterPress, this, std::placeholders::_1));
}

void MatchForm::clickCard()
{
    controller->clickCard();
}

void MatchForm::start()
{
    controller->start();
}

Match* MatchForm::getMatch()
{
    assert(match != nullptr);
    return match;
}

void MatchForm::updatePlayers()
{
    assert(match != nullptr);
    int num_players = match->getNumPlayers();
    Player* players = match->getPlayers();
    int i;
    for (i = 0; i < num_players; ++i)
    {
        tile_array[i]->injectPlayer(players[i]);
    }
    for (; i < Lobby::MAX_PLAYERS; ++i)
    {
        tile_array[i]->clear();
    }
}

void MatchForm::setDeckMeterCount(size_t size)
{
    deckMeter.setCardCount(size);
    if (size == 1) deck_size.setText("1 Card");
    deck_size.setText(std::to_string(size) + " Cards");
}

void MatchForm::setDeckMeterSize(size_t size)
{
    deckMeter.setDeckSize(size);
}

void MatchForm::pressDraw()
{
    controller->pressDraw();
}

void MatchForm::setHandName(std::string name)
{
    hand_label.setText(name + "'s Hand");
}

void MatchForm::switchPileCard()
{
    // TODO
}

void MatchForm::dealCards()
{
    state = &MatchFSM::animationState;
    console.setMessage("Dealing Cards...");
    dealCardsEventController.run(this, (size_t)match->getNumPlayers(), 7);
}

void MatchForm::setConsoleMessage(std::string msg)
{
    this->console.setText(msg);
}

void MatchForm::setConsoleWarning(std::string  msg)
{
    this->console.setWarning(msg);
}

void MatchForm::enterPress(const cursen::Event& event)
{
    switch (event.key.code)
    {
        case CursesManager::ENTER:
            state->pressEnter(*this);
        default:
            break;
    }
}

void MatchForm::setState(const MatchState* state)
{
    this->state = state;
}

MatchController* MatchForm::getController()
{
    return controller;
}

const MatchState* MatchForm::getState()
{
    return state;
}

void MatchForm::waitToBegin()
{
    controller->waitToBegin();
}

void MatchForm::beginGame()
{
    setConsoleMessage("Beginning Game");
}
