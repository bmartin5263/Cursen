//
// Created by Brandon Martin on 8/21/19.
//

#ifndef CURSEN_POINTTALLYANIMATION_H
#define CURSEN_POINTTALLYANIMATION_H

#include "Cursen/Drawing/Animation.h"

class MatchForm;
class PointTallyAnimation
{

public:

    PointTallyAnimation();

    void setForm(MatchForm* matchForm);
    void run(int winner, int points_won);

private:

    MatchForm* matchForm;
    cursen::Animation point_animation;
    std::string winner_name;
    int winner;
    int current_player;
    int points_won;
    int point_accumulator;
};

#endif //CURSEN_POINTTALLYANIMATION_H
