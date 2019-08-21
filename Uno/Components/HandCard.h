//
// Created by Brandon Martin on 7/4/19.
//

#ifndef CURSEN_HANDCARD_H
#define CURSEN_HANDCARD_H

#include "Cursen/Components/AggregateComponent.h"
#include "Cursen/Components/Label.h"
#include "Cursen/Components/Box.h"
#include "Uno/GameObjects/Card.h"

class HandCard : public cursen::AggregateComponent
{

public:

    HandCard();
    HandCard(cursen::Vect2 pos);

    void setHidden(bool value) override;
    void setForeground(const cursen::Color& color) override;

    void clear();

    void setLeft();
    void setRight();

    void hoverOn();
    void hoverOff();

    void injectCard(const Card& card);

    void initialize() override;

private:

    cursen::Label upperLabel;
    cursen::Label lowerLabel;
    cursen::Box border;
    cursen::Color color;
    bool hovered;
    bool wild;
};


#endif //CURSEN_HANDCARD_H
