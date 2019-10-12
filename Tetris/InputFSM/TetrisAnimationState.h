//
// Created by Brandon Martin on 10/12/19.
//

#ifndef CURSEN_TETRISANIMATIONSTATE_H
#define CURSEN_TETRISANIMATIONSTATE_H

#include "InputState.h"

class TetrisAnimationState : public InputState
{
    void pressDrop(const GameForm& game_form) const override;
    void pressRotate(const GameForm& game_form) const override;
    void pressLeft(const GameForm& game_form) const override;
    void pressRight(const GameForm& game_form) const override;
    void update(GameForm& game_form) const override;

};


#endif //CURSEN_ANIMATIONSTATE_H
