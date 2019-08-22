//
// Created by Brandon Martin on 4/5/19.
//

#include "Hand.h"

const Card &Hand::get(int index)
{
    return cards[index];
}

void Hand::add(const Card & card)
{
    cards.push_back(card);
}

unsigned long Hand::size() const
{
    return cards.size();
}

bool Hand::empty() const
{
    return cards.empty();
}

void Hand::remove(int index)
{
    cards.erase(cards.begin() + index);
}

bool Hand::hasPlayableCardFor(const Card& card)
{
    for (const Card& c : cards)
    {
        if (!c.isWild() && (c.getValue() == card.getValue() || c.getColor() == card.getColor()))
        {
            return true;
        }
    }
    return false;
}

size_t Hand::serialize(char* const buffer) const
{
    size_t written = 0;

    written += Serializable::Serialize(buffer + written, cards.size());
    for (const Card& card : cards)
    {
        written += card.serialize(buffer + written);
    }

    return written;
}

size_t Hand::deserialize(const char* const buffer)
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

size_t Hand::sizeOf() const
{
    return sizeof(Hand);
}

size_t Hand::safe_serialize(char* const buffer) const
{
    size_t written = 0;

    written += Serializable::Serialize(buffer + written, cards.size());
    for (const Card& card : cards)
    {
        Card dummy;
        written += dummy.serialize(buffer + written);
    }

    return written;
}

int Hand::getPointValue()
{
    int points = 0;
    for (auto& card : cards)
    {
        points += Card::Score(card);
    }
    return points;
}
