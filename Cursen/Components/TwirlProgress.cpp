//
// Created by Brandon Martin on 4/1/19.
//

#include <string>

#include "Cursen/Events/AlarmManager.h"
#include "Cursen/Drawing/CursesManager.h"
#include "TwirlProgress.h"

namespace cursen {

    TwirlProgress::TwirlProgress() :
            AggregateComponent()
    {
    }

    TwirlProgress::TwirlProgress(const Vect2 &pos) :
            AggregateComponent(pos) {
    }

    void TwirlProgress::initialize() {
        twirl_label.initialize();
        twirl_label.setPosition(getPosition());
        twirl_label.setText("|");
        twirl_label.setForeground(Color::WHITE);
        twirl_label.setHidden(true);
        add(&twirl_label);

        animation.setFrameDuration(.1);
        animation.add([&]() { twirl_label.setText("/"); });
        animation.add([&]() { twirl_label.setText("-"); });
        animation.add([&]() { twirl_label.setText("\\"); });
        animation.add([&]() { twirl_label.setText("|"); });
    }

    void TwirlProgress::start() {
        if (!animation.isRunning()) {
            twirl_label.setHidden(false);
            animation.start();
        }
    }

    void TwirlProgress::stop() {
        if (animation.isRunning()) {
            twirl_label.setHidden(true);
            animation.stop();
        }
    }

    void TwirlProgress::toggle() {
        if (animation.isRunning()) stop();
        else start();
    }

    void TwirlProgress::setState(const bool on) {
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
        return animation.isRunning();
    }

}