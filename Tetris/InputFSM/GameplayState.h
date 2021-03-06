//
// Created by Brandon Martin on 10/12/19.
//

#ifndef CURSEN_GAMEPLAYSTATE_H
#define CURSEN_GAMEPLAYSTATE_H


#include "InputState.h"

class GameplayState : public InputState
{
public:

    void pressDrop(const GameForm& game_form) const override;
    void pressRotate(const GameForm& game_form) const override;
    void pressLeft(const GameForm& game_form) const override;
    void pressRight(const GameForm& game_form) const override;
    void pressFall(const GameForm& game_form) const override;
    void update(GameForm& game_form) const override;

};


#endif //CURSEN_GAMEPLAYSTATE_H
