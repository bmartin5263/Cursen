//
// Created by Brandon Martin on 4/5/19.
//

#ifndef CURSEN_DECK_H
#define CURSEN_DECK_H


#include <vector>
#include "Card.h"

class Deck : public Serializable {

public:

    static const size_t SIZE = 108;
    static const size_t INITIAL_CARDS = 7;

    static void InitializeDeck(Deck& deck);

    void pushCard(const Card& card);
    Card popCard();

    const Card& peekCardAt(int index);
    const Card& peekCard();

    std::vector<Card>& getDeckContainer();

    unsigned long size() const;
    bool empty() const;

    void clear();
    size_t serialize(char* const buffer) const override;
    size_t deserialize(const char* const buffer) override;
    size_t sizeOf() const override;


private:

    std::vector<Card> cards;

};

struct RNG {
    int operator() (int n) {
        return std::rand() / (1.0 + RAND_MAX) * n;
    }
};


#endif //CURSEN_DECK_H
