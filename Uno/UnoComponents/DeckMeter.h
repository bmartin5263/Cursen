//
// Created by Brandon Martin on 6/30/19.
//

#ifndef CURSEN_DECKMETER_H
#define CURSEN_DECKMETER_H


#include "Cursen/Components/AggregateComponent.h"
#include "Cursen/Components/Box.h"
#include "Uno/UnoComponents/DeckMeterContent.h"

class DeckMeter : public cursen::AggregateComponent
{

public:

    DeckMeter();
    DeckMeter(cursen::Vect2 pos);

    void initialize() override ;

    void setDeckSize(size_t size);
    void setCardCount(size_t count);

private:

    cursen::Box border;
    DeckMeterContent meter;
    cursen::Animation low_deck;

};


#endif //CURSEN_DECKMETER_H
