//
// Created by Brandon Martin on 7/21/19.
//

#ifndef CURSEN_PLACECARDANIMATION_H
#define CURSEN_PLACECARDANIMATION_H

#include "Uno/Forms/MatchForm.h"

class PlaceCardAnimation
{

public:

    void run(MatchForm* matchForm);

private:

    MatchForm* matchForm;
    cursen::Animation place_card_animation;

};


#endif //CURSEN_PLACECARDANIMATION_H
