//
// Created by Brandon Martin on 4/5/19.
//

#ifndef CURSEN_DECK_H
#define CURSEN_DECK_H


#include <vector>
#include "Card.h"

class Deck {

public:

    static const size_t SIZE = 108;

    static void InitializeDeck(Deck& deck);

    void pushCard(const Card& card);
    Card popCard();

    const Card& peekCardAt(int index);
    const Card& peekCard();

    std::vector<Card>& getDeckContainer();

    unsigned long size();

    void clear();


private:

    std::vector<Card> cards;

};


#endif //CURSEN_DECK_H
