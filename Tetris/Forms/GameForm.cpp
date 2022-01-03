//
// Created by Brandon Martin on 9/25/19.
//

#include <Tetris/GameObjects/Tetris.h>
#include <Tetris/Utilities/UpdateTimerStrategy.h>
#include <Tetris/Utilities/NullUpdateStrategy.h>
#include <Tetris/Controllers/Controllers.h>
#include "Tetris/InputFSM/TetrisFSM.h"
#include "GameForm.h"

using namespace cursen;

GameForm::GameForm() : Form(Vect2(80,70))
{}

void GameForm::initialize()
{
    Tetromino::InitializeGraphics();

    leftBoard.initialize();
    leftBoard.setPosition(Vect2(0,0));

    rightBoard.initialize();
    rightBoard.setPosition(leftBoard.getPosition() + Vect2(41, 0));

    left_meter.initialize();
    left_meter.setPosition(Vect2(34,2));

    right_meter.initialize();
    right_meter.setPosition(Vect2(38,2));

    left_game = Tetris(cursen::Vect2(10,22), new UpdateTimerStrategy, &leftBoard);
    right_game = Tetris(cursen::Vect2(10,22), new UpdateTimerStrategy, &rightBoard);

    controller = &Controllers::localTetrisController;
    inputState = &TetrisFSM::gameplayState;
    controller->setData(this, &left_game);

    onUpdate([this]() { this->inputState->update(*this); });

    onArrowPress([this](EVENT_ARG) {
        if (event.arrowPress.right){
            inputState->pressRight(*this);
        }
        else if (event.arrowPress.left){
            inputState->pressLeft(*this);
        }
        else if (event.arrowPress.down){
            inputState->pressDrop(*this);
        }
    });

    onKeyPress([this](EVENT_ARG) {
        if (event.key.code == ' '){
            left_game.rotateLeft();
        }
        if (event.key.code == 'd' || event.key.code == 'D'){
            inputState->pressFall(*this);
        }
        left_game.updateField();
        left_game.update();
    });
}

void GameForm::update()
{
    int update_result = left_game.update();
    if (update_result > 0)
    {
        drop(left_game, update_result);
    }
    update_result = right_game.update();
    if (update_result > 0)
    {
        drop(right_game, update_result);
    }
}

void GameForm::pause()
{

}

void GameForm::drop(Tetris& game, int amount)
{
    for (int i = 0; i < amount; ++i)
    {
        DropResult result = game.drop();
        if (result.nextPiece)
        {
            if (result.rowsToClear[0] != -1)
            {
                game.runClearRowAnimation(result, amount - 1 - i, [&](){ this->clearRows(game, result); });
                inputState = &TetrisFSM::animationState;
                return;
            }
            else
            {
                game.spawnNextBlock();
            }
        }
    }
    game.updateField();
}

void GameForm::pressLeft(Tetris& game)
{
    game.moveLeft();
    game.updateField();
}

void GameForm::pressRight(Tetris& game)
{
    game.moveRight();
    game.updateField();
}

void GameForm::clearRows(Tetris& game, DropResult dropResult)
{
    game.clearRows(dropResult);
    game.spawnNextBlock();
    game.updateField();
    inputState = &TetrisFSM::gameplayState;
}

void GameForm::fall(Tetris& game)
{
    DropResult result = game.fall();
    if (result.nextPiece)
    {
        if (result.rowsToClear[0] != -1)
        {
            game.runClearRowAnimation(result, 0, [result, &game, this](){ this->clearRows(game, result); });
            inputState = &TetrisFSM::animationState;
            return;
        }
        else
        {
            game.spawnNextBlock();
        }
    }
    game.updateField();
}

