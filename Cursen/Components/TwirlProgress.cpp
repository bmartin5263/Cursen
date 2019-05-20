//
// Created by Brandon Martin on 4/1/19.
//

#include <Events/AlarmManager.h>
#include <string>
#include <Drawing/CursesManager.h>
#include "TwirlProgress.h"

TwirlProgress::TwirlProgress() :
        twirl_index(0), spinning(false)
{
}

TwirlProgress::TwirlProgress(const Vect2 &pos) :
        twirl_index(0), spinning(false)
{
}

void TwirlProgress::initialize() {
    twirl_label.initialize();
    twirl_label.setPosition(getPosition());
    twirl_label.setText("|");
    twirl_label.setForeground(Color::WHITE);
    twirl_label.setHidden(true);
    add(&twirl_label);
}

void TwirlProgress::start() {
    if (!spinning) {
        twirl_index = 0;
        AlarmManager::StartAlarm(this, std::bind(&TwirlProgress::doTwirl, this), .09);
        twirl_label.setHidden(false);
        spinning = true;
    }
}

void TwirlProgress::stop() {
    if (spinning) {
        AlarmManager::StopAlarm(this);
        twirl_label.setHidden(true);
        spinning = false;
    }
}

void TwirlProgress::doTwirl() {
    twirl_index = (twirl_index + 1) % TWIRL_LEN;
    twirl_label.setText(TWIRL[twirl_index]);
}

void TwirlProgress::toggle() {
    if (spinning) stop();
    else start();
}

void TwirlProgress::setState(const bool &on) {
    if (on) start();
    else stop();
}

void TwirlProgress::setForeground(const Color &color) {
    twirl_label.setForeground(color);
}

Color TwirlProgress::getForeground() {
    return twirl_label.getForeground();
}

void TwirlProgress::setBackground(const Color &color) {
    twirl_label.setBackground(color);
}

Color TwirlProgress::getBackground() {
    return twirl_label.getBackground();
}

void TwirlProgress::setPosition(const Vect2 &pos) {
    Component::setPosition(pos);
    twirl_label.setPosition(pos);
}

bool TwirlProgress::isSpinning() {
    return spinning;
}
