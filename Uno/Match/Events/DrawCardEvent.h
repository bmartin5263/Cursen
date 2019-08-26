//
// Created by Brandon Martin on 8/26/19.
//

#ifndef CURSEN_DRAWCARDEVENT_H
#define CURSEN_DRAWCARDEVENT_H

#include <Uno/GameObjects/Card.h>
#include <Uno/Forms/MatchForm.h>
#include "MatchEvent.h"

class DrawCardEvent : public MatchEvent
{
public:

    DrawCardEvent(int index, Card drawn_card) :
            index(index), drawn_card(drawn_card)
    {}

    void execute(MatchForm* match_form) override
    {
        match_form->drawCard(index, drawn_card);
    }

private:

    int index;
    Card drawn_card;

};

#endif //CURSEN_DRAWCARDEVENT_H
