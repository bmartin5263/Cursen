//
// Created by Brandon Martin on 7/21/19.
//

#include "PlaceCardAnimation.h"

void PlaceCardAnimation::run(MatchForm* matchForm)
{
    this->matchForm = matchForm;
    place_card_animation.add([=]() {});
}