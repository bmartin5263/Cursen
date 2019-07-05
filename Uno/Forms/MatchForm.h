//
// Created by Brandon Martin on 6/30/19.
//

#ifndef CURSEN_MATCHFORM_H
#define CURSEN_MATCHFORM_H

#include <Uno/UnoComponents/HandCard.h>
#include <Uno/UnoComponents/PlayerTile.h>
#include "Cursen/Components/Form.h"
#include "Cursen/Components/Label.h"
#include "Cursen/Components/HorizontalLine.h"
#include "Uno/UnoComponents/UnoConsole.h"
#include "Uno/UnoComponents/LowerBorder.h"
#include "Uno/UnoComponents/DeckMeter.h"
#include "Uno/UnoComponents/HandMeter.h"
#include "Cursen/Cursor/Cursor.h"

class MatchForm : public cursen::Form
{

public:

    MatchForm();

    void initialize() override;
    void clickCard();

private:

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
    HandCard card0;
    HandCard card1;
    HandCard card2;
    HandCard card3;
    HandCard card4;
    HandCard card5;
    HandCard card6;
    HandCard card7;
    HandCard card8;
    HandCard card9;
    HandCard card10;
    HandCard card11;
    HandCard card12;
    HandCard card13;
    cursen::Cursor card_cursor;
    DeckMeter deckMeter;
    PlayerTile p0Tile;
    PlayerTile p1Tile;
    PlayerTile p2Tile;
    PlayerTile p3Tile;

};


#endif //CURSEN_MATCHFORM_H
