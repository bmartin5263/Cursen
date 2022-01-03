//
// Created by Brandon Martin on 10/8/19.
//

#include "LocalTetrisController.h"
#include "Tetris/Forms/GameForm.h"

void LocalTetrisController::pressDrop()
{
    gameForm->drop(*game, 1);
}

void LocalTetrisController::pressLeft()
{
    gameForm->pressLeft(*game);
}

void LocalTetrisController::pressRight()
{
    gameForm->pressRight(*game);
}

void LocalTetrisController::handleDrop()
{

}

void LocalTetrisController::pressFall()
{
    gameForm->fall(*game);
}
