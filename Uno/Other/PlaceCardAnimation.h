//
// Created by Brandon Martin on 7/21/19.
//

#ifndef CURSEN_PLACECARDANIMATION_H
#define CURSEN_PLACECARDANIMATION_H

#include "Cursen/Drawing/Animation.h"

class MatchForm;
class PlaceCardAnimation
{

public:

    PlaceCardAnimation();

    void setForm(MatchForm* matchForm);
    void run();
    void animationEnd();

private:

    MatchForm* matchForm;
    cursen::Animation place_card_animation;

};


#endif //CURSEN_PLACECARDANIMATION_H
