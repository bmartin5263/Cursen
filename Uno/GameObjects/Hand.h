//
// Created by Brandon Martin on 4/5/19.
//

#ifndef CURSEN_HAND_H
#define CURSEN_HAND_H

#include "Card.h"
#include <vector>

class Hand : public Serializable {

public:

    const Card& get(int index);
    void add(const Card&);
    void remove(int index);

    unsigned long size() const;
    bool empty() const;
    int getPointValue();

    bool hasPlayableCardFor(const Card& card);
    size_t serialize(char* const buffer) const override;
    size_t deserialize(const char* const buffer) override;
    size_t safe_serialize(char* const buffer) const;
    size_t sizeOf() const override;


private:

    std::vector<Card> cards;

};


#endif //CURSEN_HAND_H
