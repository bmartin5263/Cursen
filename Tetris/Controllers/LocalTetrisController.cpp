//
// Created by Brandon Martin on 10/8/19.
//

#include "LocalTetrisController.h"
#include "Tetris/Forms/GameForm.h"

void LocalTetrisController::pressDrop()
{
    gameForm->drop(*game, *board, 1);
}

void LocalTetrisController::pressLeft()
{
    gameForm->pressLeft(*game, *board);
}

void LocalTetrisController::pressRight()
{
    gameForm->pressRight(*game, *board);
}

void LocalTetrisController::handleDrop()
{

}
