//
// Created by Brandon Martin on 8/11/19.
//

#ifndef CURSEN_SKIPANIMATION_H
#define CURSEN_SKIPANIMATION_H

#include "Cursen/Drawing/Animation.h"

class MatchForm;
class SkipAnimation
{

public:

    SkipAnimation();

    void setForm(MatchForm* matchForm);
    void run(int player_index);

private:

    MatchForm* matchForm;
    cursen::Animation skip_animation;
    int player_index;

};

#endif //CURSEN_SKIPANIMATION_H
