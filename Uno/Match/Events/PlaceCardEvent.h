//
// Created by Brandon Martin on 8/26/19.
//

#ifndef CURSEN_PLACECARDEVENT_H
#define CURSEN_PLACECARDEVENT_H

#include "MatchEvent.h"
#include "Uno/Forms/MatchForm.h"

class PlaceCardEvent : public MatchEvent
{
public:

    PlaceCardEvent(int index, int played_card_index, const Card& played_card) :
        index(index), played_card_index(played_card_index), played_card(played_card)
    {}

    void execute(MatchForm* match_form) override
    {
        match_form->playCard(index, played_card_index, played_card);
    }

private:

    int index;
    int played_card_index;
    Card played_card;

};

#endif //CURSEN_PLACECARDEVENT_H
