//
// Created by Brandon Martin on 4/5/19.
//

#include "Deck.h"

void Deck::InitializeDeck(Deck& deck)
{
    deck.clear();
    for (CardColors color : Card::COLORS)
    {
        for (CardValues value : Card::VALUES_NO_WILD)
        {
            deck.pushCard(Card(color, value));
            if (value != CardValues::ZERO)
            {
                // Zeros only get one card
                deck.pushCard(Card(color, value));
            }
        }
    }
    for (int i = 0; i < 4; ++i)
    {
        deck.pushCard(Card(CardColors::WHITE, CardValues::WILD));
        deck.pushCard(Card(CardColors::WHITE, CardValues::PLUS_4));
    }
    std::random_shuffle(deck.getDeckContainer().begin(), deck.getDeckContainer().end());
}

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

const Card& Deck::peekCardAt(int index)
{
    return cards[index];
}

unsigned long Deck::size()
{
    return cards.size();
}

void Deck::clear()
{
    cards.clear();
}

std::vector<Card>& Deck::getDeckContainer()
{
    return cards;
}
