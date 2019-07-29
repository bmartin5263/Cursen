//
// Created by Brandon Martin on 4/5/19.
//

#include <cassert>
#include "Deck.h"

void Deck::InitializeDeck(Deck& deck)
{
    deck.clear();
    for (CardColor color : Card::COLORS)
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
        deck.pushCard(Card(CardColor::WHITE, CardValues::WILD));
        deck.pushCard(Card(CardColor::WHITE, CardValues::PLUS_4));
    }
    std::random_shuffle(deck.getDeckContainer().begin(), deck.getDeckContainer().end(), RNG());
}

void Deck::pushCard(const Card& card) {
    cards.push_back(card);
}

Card Deck::popCard() {
    assert(!cards.empty());
    Card card = cards.back();
    cards.pop_back();
    return card;
}

const Card &Deck::peekCard() {
    assert(!cards.empty());
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

size_t Deck::serialize(char* const buffer) const
{
    size_t written = 0;

    written += Serializable::Serialize(buffer + written, cards.size());
    for (const Card& card : cards)
    {
        written += card.serialize(buffer + written);
    }

    return written;
}

size_t Deck::deserialize(const char* const buffer)
{
    size_t read = 0;

    unsigned long size;
    read += Serializable::Deserialize(buffer + read, size);

    if (size > 0) {
        cards.reserve(size);
        for (unsigned long i = 0; i < size; ++i)
        {
            Card c;
            read += c.deserialize(buffer + read);
            cards.push_back(c);
        }
    }

    return read;
}

size_t Deck::sizeOf() const
{
    return sizeof(Deck);
}
