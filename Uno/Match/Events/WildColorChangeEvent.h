//
// Created by Brandon Martin on 8/26/19.
//

#ifndef CURSEN_WILDCOLORCHANGEEVENT_H
#define CURSEN_WILDCOLORCHANGEEVENT_H

#include <Uno/GameObjects/CardColor.h>
#include <Uno/Forms/MatchForm.h>
#include "MatchEvent.h"

class WildColorChangeEvent : public MatchEvent
{
public:

    WildColorChangeEvent(CardColor color) :
        color(color)
    {}

    void execute(MatchForm* match_form) override
    {
        match_form->wildColorChange(color);
    }

private:

    CardColor color;

};

#endif //CURSEN_WILDCOLORCHANGEEVENT_H
