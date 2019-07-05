//
// Created by Brandon Martin on 6/30/19.
//

#include "MatchForm.h"
#include "Cursen/CursenApplication.h"

using namespace cursen;

MatchForm::MatchForm() :
        Form(cursen::Vect2(70, 33))
{
}

void MatchForm::initialize()
{
    welcome.initialize();
    welcome.setPosition(Vect2(0,0));
    welcome.setText("Welcome to the Match!");
    welcome.onEscapePress([](const Event e) { CursenApplication::CloseForm(); });

    console.initialize();
    console.setText("Welcome!");

    lowerBorder.initialize();
    lowerBorder.setPosition(Vect2(0, 6));

    deck_label.initialize();
    deck_label.setPosition(Vect2(1, 8));
    deck_label.setText("Deck:");

    hand_label.initialize();
    hand_label.setPosition(Vect2(1, 24));
    hand_label.setText("Unknown");

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
    p0Tile.injectPlayer(Player("Fuckzo", PlayerColor::RED, 12));

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
    card0.setHidden(false);
    card0.onClick(std::bind(&MatchForm::clickCard, this));

    card1.initialize();
    card1.setPosition(Vect2(11, 27));
    card1.setHidden(false);
    card1.onClick(std::bind(&MatchForm::clickCard, this));

    card2.initialize();
    card2.setPosition(Vect2(15, 27));
    card2.setHidden(false);
    card2.onClick(std::bind(&MatchForm::clickCard, this));

    card3.initialize();
    card3.setPosition(Vect2(19, 27));
    card3.setHidden(false);
    card3.onClick(std::bind(&MatchForm::clickCard, this));

    card4.initialize();
    card4.setPosition(Vect2(23, 27));
    card4.setHidden(false);
    card4.onClick(std::bind(&MatchForm::clickCard, this));

    card5.initialize();
    card5.setPosition(Vect2(27, 27));
    card5.setHidden(false);
    card5.onClick(std::bind(&MatchForm::clickCard, this));

    card6.initialize();
    card6.setPosition(Vect2(31, 27));
    card6.setHidden(false);
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

    card0.injectCard(Card(CardColors::BLUE, CardValues::EIGHT));
    card1.injectCard(Card(CardColors::RED, CardValues::SKIP));
    card2.injectCard(Card(CardColors::RED, CardValues::SEVEN));
    card3.injectCard(Card(CardColors::YELLOW, CardValues::EIGHT));
    card4.injectCard(Card(CardColors::BLUE, CardValues::FOUR));
    card5.injectCard(Card(CardColors::GREEN, CardValues::FIVE));
    card6.injectCard(Card(CardColors::GREEN, CardValues::WILD));

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

}

void MatchForm::clickCard()
{
    console.setText("Card Clicked!");
}

