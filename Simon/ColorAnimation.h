//
// Created by Brandon Martin on 9/11/19.
//

#ifndef CURSEN_COLORANIMATION_H
#define CURSEN_COLORANIMATION_H


#include <Cursen/Drawing/Animation.h>

class SimonForm;
class ColorAnimation
{

public:

    ColorAnimation(SimonForm* simonForm);

    void start();

private:

    SimonForm* form;
    cursen::Animation animation;
    int index;

};


#endif //CURSEN_COLORANIMATION_H
