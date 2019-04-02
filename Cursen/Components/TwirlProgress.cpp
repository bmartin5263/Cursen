//
// Created by Brandon Martin on 4/1/19.
//

#include <Events/AlarmManager.h>
#include <string>
#include <Drawing/CursesManager.h>
#include "TwirlProgress.h"

TwirlProgress::TwirlProgress(const Size &pos) :
        ColorComponent(pos, Size(0,0)), twirlIndex(0), spinning(false)
{
    initialize();
}

void TwirlProgress::initialize() {
    ColorComponent::initialize();

    twirl_label = new Label(position, Size(1,1));
    twirl_label->setText("|");
    twirl_label->setForeground(Color::WHITE);
    twirl_label->setHidden(true);
    add(twirl_label);
}

void TwirlProgress::start() {
    if (!spinning) {
        AlarmManager::StartTimer(this, std::bind(&TwirlProgress::doTwirl, this), .1);
        twirl_label->setHidden(false);
        spinning = true;
    }
}

void TwirlProgress::stop() {
    if (spinning) {
        AlarmManager::StopTimer(this);
        twirl_label->setHidden(true);
        spinning = false;
    }
}

void TwirlProgress::doTwirl() {
    twirlIndex = (twirlIndex + 1) % TWIRL_LEN;
    twirl_label->setText(TWIRL[twirlIndex]);
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
    twirl_label->setForeground(color);
}

Color TwirlProgress::getForeground() {
    return twirl_label->getForeground();
}

void TwirlProgress::setBackground(const Color &color) {
    twirl_label->setBackground(color);
}

Color TwirlProgress::getBackground() {
    return twirl_label->getBackground();
}
