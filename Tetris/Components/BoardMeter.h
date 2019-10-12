//
// Created by Brandon Martin on 10/10/19.
//

#ifndef CURSEN_BOARDMETER_H
#define CURSEN_BOARDMETER_H


#include <Cursen/Components/AggregateComponent.h>
#include <Cursen/Components/Box.h>
#include <Cursen/Components/BitMap.h>

class BoardMeter : public cursen::AggregateComponent
{

public:

    BoardMeter();
    void initialize() override;

    void fill(int amt);
    void spill(int amt);

private:

    int filled_index;

    cursen::Box border;
    cursen::BitMap meter;

};


#endif //CURSEN_BOARDMETER_H
