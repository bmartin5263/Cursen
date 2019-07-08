//
// Created by Brandon Martin on 6/30/19.
//

#include <cassert>

#include <Uno/Match/MatchControllers.h>
#include "MatchForm.h"
#include "Cursen/CursenApplication.h"

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
    welcome.initialize();
    welcome.setPosition(Vect2(0,0));
    welcome.setText("Welcome to the Match!");
    welcome.onEscapePress([](const Event e) { CursenApplication::CloseForm(); });
    welcome.onDeletePress([&](const Event e) {
        front_card.shrink();
    });
    welcome.onKeyPress([&](const Event e) {
        if (e.key.code == 'g') front_card.grow();
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
    hand_box.setFill(Content::INVISIBLE);
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

    card0.initialize();
    card0.setPosition(Vect2(7, 27));
    card0.setHidden(true);
    card0.onClick(std::bind(&MatchForm::clickCard, this));

    card1.initialize();
    card1.setPosition(Vect2(11, 27));
    card1.setHidden(true);
    card1.onClick(std::bind(&MatchForm::clickCard, this));

    card2.initialize();
    card2.setPosition(Vect2(15, 27));
    card2.setHidden(true);
    card2.onClick(std::bind(&MatchForm::clickCard, this));

    card3.initialize();
    card3.setPosition(Vect2(19, 27));
    card3.setHidden(true);
    card3.onClick(std::bind(&MatchForm::clickCard, this));

    card4.initialize();
    card4.setPosition(Vect2(23, 27));
    card4.setHidden(true);
    card4.onClick(std::bind(&MatchForm::clickCard, this));

    card5.initialize();
    card5.setPosition(Vect2(27, 27));
    card5.setHidden(true);
    card5.onClick(std::bind(&MatchForm::clickCard, this));

    card6.initialize();
    card6.setPosition(Vect2(31, 27));
    card6.setHidden(true);
    card6.onClick(std::bind(&MatchForm::clickCard, this));

    card7.initialize();
    card7.setPosition(Vect2(35, 27));
    card7.setHidden(true);
    card7.onClick(std::bind(&MatchForm::clickCard, this));

    card8.initialize();
    card8.setPosition(Vect2(39, 27));
    card8.setHidden(true);
    card8.onClick(std::bind(&MatchForm::clickCard, this));

    card9.initialize();
    card9.setPosition(Vect2(43, 27));
    card9.setHidden(true);
    card9.onClick(std::bind(&MatchForm::clickCard, this));

    card10.initialize();
    card10.setPosition(Vect2(47, 27));
    card10.setHidden(true);
    card10.onClick(std::bind(&MatchForm::clickCard, this));

    card11.initialize();
    card11.setPosition(Vect2(51, 27));
    card11.setHidden(true);
    card11.onClick(std::bind(&MatchForm::clickCard, this));

    card12.initialize();
    card12.setPosition(Vect2(55, 27));
    card12.setHidden(true);
    card12.onClick(std::bind(&MatchForm::clickCard, this));

    card13.initialize();
    card13.setPosition(Vect2(59, 27));
    card13.setHidden(true);
    card13.onClick(std::bind(&MatchForm::clickCard, this));

    //back_card.initialize();
    back_card.initialize();
    back_card.setPosition(Vect2(27,8));
    back_card.setForeground(Color::WHITE);

    front_card.initialize();
    front_card.setPosition(Vect2(29,10));
    front_card.setDrawOrder(back_card.getDrawOrder() + 10);

    card_cursor.moveTo(&card0);
    card_cursor.mapComponent(&card0, ArrowMap(&card13, nullptr, &card1, nullptr));
    card_cursor.mapComponent(&card1, ArrowMap(&card0, nullptr, &card2, nullptr));
    card_cursor.mapComponent(&card2, ArrowMap(&card1, nullptr, &card3, nullptr));
    card_cursor.mapComponent(&card3, ArrowMap(&card2, nullptr, &card4, nullptr));
    card_cursor.mapComponent(&card4, ArrowMap(&card3, nullptr, &card5, nullptr));
    card_cursor.mapComponent(&card5, ArrowMap(&card4, nullptr, &card6, nullptr));
    card_cursor.mapComponent(&card6, ArrowMap(&card5, nullptr, &card7, nullptr));
    card_cursor.mapComponent(&card7, ArrowMap(&card6, nullptr, &card8, nullptr));
    card_cursor.mapComponent(&card8, ArrowMap(&card7, nullptr, &card9, nullptr));
    card_cursor.mapComponent(&card9, ArrowMap(&card8, nullptr, &card10, nullptr));
    card_cursor.mapComponent(&card10, ArrowMap(&card9, nullptr, &card11, nullptr));
    card_cursor.mapComponent(&card11, ArrowMap(&card10, nullptr, &card12, nullptr));
    card_cursor.mapComponent(&card12, ArrowMap(&card11, nullptr, &card13, nullptr));
    card_cursor.mapComponent(&card13, ArrowMap(&card12, nullptr, &card0, nullptr));
    card_cursor.setEnabled(true);

    card_array[0] = &card0;
    card_array[1] = &card1;
    card_array[2] = &card2;
    card_array[3] = &card3;
    card_array[4] = &card4;
    card_array[5] = &card5;
    card_array[6] = &card6;
    card_array[7] = &card7;
    card_array[8] = &card8;
    card_array[9] = &card9;
    card_array[10] = &card10;
    card_array[11] = &card11;
    card_array[12] = &card12;
    card_array[13] = &card13;

    tile_array[0] = &p0Tile;
    tile_array[1] = &p1Tile;
    tile_array[2] = &p2Tile;
    tile_array[3] = &p3Tile;

    start();
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
    for (; i < 4; ++i)
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

