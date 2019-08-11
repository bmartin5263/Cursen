//
// Created by Brandon Martin on 7/4/19.
//

#ifndef CURSEN_HANDMETER_H
#define CURSEN_HANDMETER_H


#include "Cursen/Components/AggregateComponent.h"
#include "Cursen/Components/Label.h"

class HandMeter : public cursen::AggregateComponent
{

public:

    HandMeter();
    HandMeter(cursen::Vect2 pos);

    void initialize() override ;
    void update(int hand_size, int hand_index);

private:

    cursen::Label meter;

};


#endif //CURSEN_HANDMETER_H
