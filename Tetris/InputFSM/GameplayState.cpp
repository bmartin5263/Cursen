//
// Created by Brandon Martin on 10/12/19.
//

#include <Tetris/Forms/GameForm.h>
#include <Tetris/Controllers/TetrisController.h>
#include "GameplayState.h"

void GameplayState::pressDrop(const GameForm& game_form) const
{
    game_form.getController().pressDrop();
}

void GameplayState::pressRotate(const GameForm& game_form) const
{
    game_form.getController().pressDrop();
}

void GameplayState::pressLeft(const GameForm& game_form) const
{
    game_form.getController().pressLeft();
}

void GameplayState::pressRight(const GameForm& game_form) const
{
    game_form.getController().pressRight();
}

void GameplayState::update(GameForm& game_form) const
{
    game_form.update();
}
