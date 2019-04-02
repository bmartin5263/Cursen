//
// Created by Brandon Martin on 4/1/19.
//

#include <Events/AlarmManager.h>
#include <string>
#include <Drawing/CursesManager.h>
#include "TwirlProgress.h"

TwirlProgress::TwirlProgress(const Vect2i &pos) :
        ColorComponent(pos, Vect2i(0,0)), spinning(false)
{
    initialize();
}

void TwirlProgress::initialize() {
    ColorComponent::initialize();

    twirl_label = new Label(position, Vect2i(1,1));
    twirl_label->setText("|");
    twirl_label->setForeground(Color::WHITE);
    twirl_label->setHidden(true);
    add(twirl_label);
}

void TwirlProgress::start() {
    AlarmManager::StartTimer(this, std::bind(&TwirlProgress::doTwirl, this), .1);
    twirl_label->setHidden(false);
    spinning = true;
}

void TwirlProgress::stop() {
    AlarmManager::StopTimer(this);
    twirl_label->setHidden(true);
    spinning = false;
}

void TwirlProgress::doTwirl() {
    static int counter = 0;
    counter = (counter + 1) % TWIRL_LEN;
    twirl_label->setText(TWIRL[counter]);
}

void TwirlProgress::toggle() {
    if (spinning) stop();
    else start();
}