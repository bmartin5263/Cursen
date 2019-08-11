//
// Created by Brandon Martin on 8/11/19.
//

#ifndef CURSEN_REVERSEANIMATION_H
#define CURSEN_REVERSEANIMATION_H


#include "Cursen/Drawing/Animation.h"

class MatchForm;
class ReverseAnimation
{

public:

    ReverseAnimation();

    void setForm(MatchForm* matchForm);
    void run(int index_modifier, bool is_first_card);

private:

    MatchForm* matchForm;
    cursen::Animation reverse_animation;
    int index_modifier;
    int current_index;
    bool first_card;

};


#endif //CURSEN_REVERSEANIMATION_H
