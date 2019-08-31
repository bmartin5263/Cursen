//
// Created by Brandon Martin on 8/11/19.
//

#include <Uno/Match/FSM/MatchFSM.h>
#include "SkipAnimation.h"
#include "Uno/Forms/MatchForm.h"

SkipAnimation::SkipAnimation()
{
    skip_animation.setInfinite(false);
    skip_animation.setVariableTime(false);
    skip_animation.setFrameDuration(.3);
    skip_animation.add([this]() { matchForm->getPlayerTile(player_index).setForeground(cursen::Color::GRAY); });
    skip_animation.add([this]() { matchForm->getPlayerTile(player_index).colorize(); });
    skip_animation.add([this]() { matchForm->getPlayerTile(player_index).setForeground(cursen::Color::GRAY); });
    skip_animation.add([this]() { matchForm->getPlayerTile(player_index).colorize(); });
    skip_animation.add([this]() { matchForm->getPlayerTile(player_index).colorize(); });
    skip_animation.onEnd([this]() {
        if (matchForm->getMatch().getCurrentTurn() == player_index) matchForm->advanceTurn(1);
        else matchForm->advanceTurn(2);
        if (matchForm->getMatch().getPlayer(player_index).getHandSize() == 1)
        {
            matchForm->addPlayerToUno(&matchForm->getPlayerTile(player_index));
        }
        matchForm->getMatchEventQueue().popEvent();
    });
}

void SkipAnimation::setForm(MatchForm* matchForm)
{
    this->matchForm = matchForm;
}


void SkipAnimation::run(int player_index)
{
    matchForm->setState(&MatchFSM::animationState);
    this->player_index = player_index;
    Match& match = matchForm->getMatch();
    if (match.getPile().size() == 1) this->player_index = match.getCurrentTurn();
    else this->player_index = match.peekNextTurn();

    skip_animation.start();
}
