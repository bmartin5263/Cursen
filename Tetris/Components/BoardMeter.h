//
// Created by Brandon Martin on 10/10/19.
//

#ifndef CURSEN_BOARDMETER_H
#define CURSEN_BOARDMETER_H


#include <Cursen/Components/AggregateComponent.h>
#include <Cursen/Components/Box.h>

class BoardMeter : public cursen::AggregateComponent
{

public:

    BoardMeter();
    void initialize() override;

private:

    cursen::Box border;

};


#endif //CURSEN_BOARDMETER_H
