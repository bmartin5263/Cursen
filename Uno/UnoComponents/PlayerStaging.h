//
// Created by Brandon Martin on 4/10/19.
//

#ifndef CURSEN_PLAYERSTAGING_H
#define CURSEN_PLAYERSTAGING_H


#include "Components/AggregateComponent.h"
#include "Components/Box.h"
#include "Stage.h"

class PlayerStaging : public AggregateComponent {

public:

    PlayerStaging();
    PlayerStaging(const Size& loc);

    void initialize() override;

    void startSearching();
    void stopSearching();

private:

    Box border;
    Stage p1Stage;
    Stage p2Stage;
    Stage p3Stage;
    Stage p4Stage;
    bool spinning;

};


#endif //CURSEN_PLAYERSTAGING_H
