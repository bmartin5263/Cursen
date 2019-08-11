//
// Created by Brandon Martin on 7/21/19.
//

#include <Uno/Match/FSM/MatchFSM.h>
#include "PlaceCardAnimation.h"
#include "Uno/Forms/MatchForm.h"
#include "Uno/GameObjects/Match.h"

PlaceCardAnimation::PlaceCardAnimation()
{
    place_card_animation.add([=]() { matchForm->getFrontCard().setHidden(false); });
    place_card_animation.add([=]() { matchForm->getFrontCard().grow(); });
    place_card_animation.add([=]() { matchForm->getFrontCard().grow(); });
    place_card_animation.add([=]() { matchForm->getFrontCard().grow(); });
    place_card_animation.add([=]() { matchForm->getFrontCard().grow(); });
    place_card_animation.add([=]() { matchForm->getFrontCard().grow(); });
    place_card_animation.add([=]() { matchForm->getFrontCard().grow(); });
    place_card_animation.add([=]() { matchForm->getFrontCard().grow(); });
    place_card_animation.add([=]() { matchForm->getFrontCard().grow(); });
    place_card_animation.add([=]() { matchForm->getFrontCard().grow(); });
    place_card_animation.add([=]() { matchForm->getFrontCard().grow(); });
    place_card_animation.setVariableTime(false);
    place_card_animation.setFrameDuration(.04);
    place_card_animation.setInifinite(false);
    place_card_animation.onEnd(
            [this]() { animationEnd(); }
    );
}

void PlaceCardAnimation::setForm(MatchForm* matchForm)
{
    this->matchForm = matchForm;
}


void PlaceCardAnimation::run()
{
    matchForm->getFrontCard().shrinkCompletely();
    matchForm->getFrontCard().setHidden(true);
    place_card_animation.start();
    matchForm->setState(&MatchFSM::animationState);
}

void PlaceCardAnimation::animationEnd()
{
    matchForm->getFrontCard().setNumberHidden(false);
    matchForm->getFrontCard().setSize(cursen::Vect2(14, 12));
    matchForm->interpretCard();
}
