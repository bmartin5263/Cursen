//
// Created by Brandon Martin on 8/11/19.
//

#include "ReverseAnimation.h"
#include "Uno/Forms/MatchForm.h"

ReverseAnimation::ReverseAnimation()
{
    reverse_animation.setInfinite(false);
    reverse_animation.setVariableTime(false);
    reverse_animation.setFrameDuration(.04);
    reverse_animation.setLoops(9);
    reverse_animation.add([this]() {
        matchForm->getFrontCard().setReverseFace(current_index);
        current_index = current_index + index_modifier;
    });

    reverse_animation.onEnd([this]() {
        matchForm->advanceTurn(first_card ? 0 : 1);
        matchForm->getMatchEventQueue().popEvent();
    });
}

void ReverseAnimation::setForm(MatchForm* matchForm)
{
    this->matchForm = matchForm;
}

void ReverseAnimation::run(int index_modifier, bool is_first_card)
{
    this->first_card = is_first_card;
    this->index_modifier = index_modifier;
    if (index_modifier == -1) current_index = 9;
    else current_index = 0;
    reverse_animation.start();
}
