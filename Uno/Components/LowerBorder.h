//
// Created by Brandon Martin on 6/30/19.
//

#ifndef CURSEN_LOWERBORDER_H
#define CURSEN_LOWERBORDER_H


#include "Cursen/Components/AggregateComponent.h"
#include "Cursen/Components/Box.h"


class LowerBorder : public cursen::AggregateComponent
{

public:

    void initialize() override;

private:

    cursen::Box border;

};


#endif //CURSEN_LOWERBORDER_H
