//
// Created by Brandon Martin on 7/15/19.
//

#include "DealCardsEventAnimation.h"
#include "Uno/Forms/MatchForm.h"
#include "Uno/GameObjects/Match.h"
#include <functional>
#include <cassert>
#include <Uno/Match/FSM/MatchFSM.h>

void DealCardsEventController::run(MatchForm* matchForm, size_t num_players, size_t cards_to_deal)
{
    assert(cards_to_deal > 0);
    this->maxPlayers = num_players;
    this->currentPlayer = 0;
    this->matchForm = matchForm;

    card_deal_animation.clear();
    card_deal_animation.add([&]()
    {
        this->matchForm->drawCardByIndex((int)currentPlayer);
    });
    card_deal_animation.setVariableTime(false);
    card_deal_animation.setFrameDuration(.1);
    card_deal_animation.setLoops(cards_to_deal - 1);
    card_deal_animation.onEnd(
            [&]() {this->loopEnd();}
    );
    card_deal_animation.start(false);
}

void DealCardsEventController::loopEnd()
{
    this->currentPlayer++;
    if (this->currentPlayer < maxPlayers)
    {
        card_deal_animation.start(false);
    }
    else
    {
        matchForm->waitToBegin();
    }
}
