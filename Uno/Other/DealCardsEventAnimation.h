//
// Created by Brandon Martin on 7/15/19.
//

#ifndef CURSEN_DEALCARDSEVENTCONTROLLER_H
#define CURSEN_DEALCARDSEVENTCONTROLLER_H

#include "Cursen/Drawing/Animation.h"

class MatchForm;
class DealCardsEventAnimation
{

public:

    DealCardsEventAnimation();
    ~DealCardsEventAnimation() = default;

    void run(MatchForm* matchForm, size_t num_players, size_t cards_to_deal, size_t deck_size);

private:

    void loopEnd();

    size_t currentPlayer;
    size_t maxPlayers;
    size_t count;
    size_t deck_size;
    MatchForm* matchForm;

    cursen::Animation card_deal_animation;

};


#endif //CURSEN_DEALCARDSEVENTCONTROLLER_H
