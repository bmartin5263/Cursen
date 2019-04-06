//
// Created by Brandon Martin on 4/5/19.
//

#ifndef CURSEN_DECK_H
#define CURSEN_DECK_H


#include <vector>
#include "Card.h"

class Deck {

public:

    void pushCard(const Card& card);
    Card popCard();

    const Card& peekCardAt(int index);
    const Card& peekCard();

    unsigned long size();


private:

    std::vector<Card> cards;

};


#endif //CURSEN_DECK_H
