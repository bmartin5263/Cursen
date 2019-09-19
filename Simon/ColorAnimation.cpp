//
// Created by Brandon Martin on 9/11/19.
//

#include "ColorAnimation.h"
#include "SimonForm.h"

ColorAnimation::ColorAnimation(SimonForm* simonForm) : form(simonForm)
{
    animation.setVariableTime(false);
    animation.setInfinite(false);
    animation.setFrameDuration(.6);
    animation.add([this]() {
        form->flash(form->getSimon().getOrder().at((unsigned long)index++));
    });
    animation.onEnd([this]() {
        cursen::AlarmManager::SetTimeout([this]() { this->form->startGuessing(); }, .5);
    });
}

void ColorAnimation::start()
{
    size_t loops = form->getSimon().getOrder().size();
    index = 0;
    animation.setLoops(loops - 1);
    animation.start(3.0);
}
