//
// Created by Brandon Martin on 4/10/19.
//

#ifndef CURSEN_MODESELECTBOX_H
#define CURSEN_MODESELECTBOX_H


#include "Components/AggregateComponent.h"
#include "Components/Label.h"
#include "Components/Box.h"
#include "Components/Button.h"
#include "Stage.h"

class ModeSelectBox : public AggregateComponent {

public:

    ModeSelectBox();
    ModeSelectBox(const Size& pos);

    void initialize() override;

private:

    Box border;
    Box console_box;
    Label console_message;
    Stage player_stage;
    Button local_button;
    Button host_button;
    Button join_button;
    Button exit_button;

};


#endif //CURSEN_MODESELECTBOX_H
