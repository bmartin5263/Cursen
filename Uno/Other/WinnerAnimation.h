//
// Created by Brandon Martin on 8/20/19.
//

#ifndef CURSEN_WINNERANIMATION_H
#define CURSEN_WINNERANIMATION_H

#include "Cursen/Drawing/Animation.h"

class MatchForm;
class WinnerAnimation
{

public:

    WinnerAnimation();

    void setForm(MatchForm* matchForm);
    void run(int winner);

private:

    MatchForm* matchForm;
    cursen::Animation winner_animation;
    int winner;

};


#endif //CURSEN_WINNERANIMATION_H
