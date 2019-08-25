//
// Created by Brandon Martin on 8/20/19.
//

#include <Uno/Match/FSM/MatchFSM.h>
#include "Uno/Forms/MatchForm.h"
#include "WinnerAnimation.h"

using namespace cursen;

WinnerAnimation::WinnerAnimation()
{
    winner_animation.setInfinite(false);
    winner_animation.setLoops(5);
    winner_animation.setVariableTime(false);
    winner_animation.setFrameDuration(.06);
    winner_animation.add([this]() {
        matchForm->getPlayerTile(winner).setForeground(Color::MAGENTA);
        matchForm->getConsole().setForeground(Color::MAGENTA);
    });
    winner_animation.add([this]() {
        matchForm->getPlayerTile(winner).setForeground(Color::ORANGE);
        matchForm->getConsole().setForeground(Color::ORANGE);
    });
    winner_animation.add([this]() {
        matchForm->getPlayerTile(winner).setForeground(Color::YELLOW);
        matchForm->getConsole().setForeground(Color::YELLOW);
    });
    winner_animation.add([this]() {
        matchForm->getPlayerTile(winner).setForeground(Color::GREEN);
        matchForm->getConsole().setForeground(Color::GREEN);
    });
    winner_animation.add([this]() {
        matchForm->getPlayerTile(winner).setForeground(Color::BLUE);
        matchForm->getConsole().setForeground(Color::BLUE);
    });
    winner_animation.add([this]() {
        matchForm->getPlayerTile(winner).setForeground(Color::LAVENDER);
        matchForm->getConsole().setForeground(Color::LAVENDER);
    });
    winner_animation.onEnd([this]() {
        matchForm->getPlayerTile(winner).colorize();
        matchForm->getConsole().setMessage("Tallying Points");
        AlarmManager::SetTimeout([this]() { matchForm->tallyPoints(winner); }, 2.0);
    });
}

void WinnerAnimation::setForm(MatchForm* matchForm)
{
    this->matchForm = matchForm;
}


void WinnerAnimation::run(int winner)
{
    this->winner = winner;
    matchForm->getPlayerTile(winner).unhighlight();
    matchForm->setConsoleMessage(matchForm->getMatch().getPlayer(winner).getName() + " Wins!");
    winner_animation.start();
    matchForm->setState(&MatchFSM::animationState);
}
