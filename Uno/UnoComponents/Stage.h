//
// Created by Brandon Martin on 4/10/19.
//

#ifndef CURSEN_STAGE_H
#define CURSEN_STAGE_H


#include "Components/AggregateComponent.h"
#include "Components/Box.h"
#include "Components/Label.h"
#include "Components/TwirlProgress.h"

class Stage : public AggregateComponent {

public:

    Stage();
    Stage(const Size& pos);

    void initialize() override;
    void toggleSearch();

private:

    Box border;
    Label playerName;
    Label points;
    TwirlProgress search_progress;

};


#endif //CURSEN_STAGE_H
