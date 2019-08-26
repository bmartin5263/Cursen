//
// Created by Brandon Martin on 8/21/19.
//

#include "GameoverState.h"
#include "Uno/Forms/MatchForm.h"

void GameoverState::pressEnter(MatchForm& matchForm) const
{
    matchForm.getController()->endGame();
}

void GameoverState::pressD(MatchForm& matchForm) const
{
    matchForm.getController()->endGame();
}

void GameoverState::pressSpace(MatchForm& matchForm) const
{
    matchForm.getController()->endGame();
}

void GameoverState::pressB(MatchForm& matchForm) const
{
    matchForm.getController()->endGame();
}

void GameoverState::pressR(MatchForm& matchForm) const
{
    matchForm.getController()->endGame();
}

void GameoverState::pressY(MatchForm& matchForm) const
{
    matchForm.getController()->endGame();
}

void GameoverState::pressG(MatchForm& matchForm) const
{
    matchForm.getController()->endGame();
}

void GameoverState::pressP(MatchForm& matchForm) const
{
    matchForm.getController()->endGame();
}

void GameoverState::pressAnyOtherButton(MatchForm& matchForm) const
{
    matchForm.getController()->endGame();
}
