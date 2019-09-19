//
// Created by Brandon Martin on 9/11/19.
//

#ifndef CURSEN_SIMONFORM_H
#define CURSEN_SIMONFORM_H


#include <Cursen/Components/Form.h>
#include <Cursen/Components/Box.h>
#include "ColorButton.h"
#include "Simon.h"
#include "ColorAnimation.h"

class SimonForm : public cursen::Form
{
public:

    SimonForm();

    void initialize() override;
    void showPattern();
    void flash(int index);

    void nextRound();
    void startGuessing();
    void makeGuess(int guess);
    Simon& getSimon() { return simon; };

private:

    Simon simon;

    cursen::Label msg;
    cursen::Label level;
    cursen::Box border;
    ColorButton button[4];

    cursen::Animation count_down;
    ColorAnimation colorAnimation;

    bool requesting_input;
    bool gameover;
};


#endif //CURSEN_SIMONFORM_H
