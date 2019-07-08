//
// Created by Brandon Martin on 4/5/19.
//

#ifndef CURSEN_HAND_H
#define CURSEN_HAND_H

#include "Card.h"
#include <vector>

class Hand {

public:

    const Card& get(int index);
    void add(const Card&);
    void remove(int index);

    unsigned long size() const;
    bool empty() const;

private:

    std::vector<Card> cards;

};


#endif //CURSEN_HAND_H
