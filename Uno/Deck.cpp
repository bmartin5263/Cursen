//
// Created by Brandon Martin on 4/5/19.
//

#include "Deck.h"

void Deck::pushCard(const Card& card) {
    cards.push_back(card);
}

Card Deck::popCard() {
    if (cards.empty()) {
        throw std::underflow_error("Deck Underflow");
    }
    Card card = cards.back();
    cards.pop_back();
    return card;
}

const Card &Deck::peekCard() {
    if (cards.empty()) {
        throw std::underflow_error("Deck Underflow");
    }
    return cards.back();
}

const Card& Deck::peekCardAt(int index) {
    return cards[index];
}

unsigned long Deck::size() {
    return cards.size();
}
