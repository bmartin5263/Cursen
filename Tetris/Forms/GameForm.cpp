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

    controller = &Controllers::localTetrisController;
    inputState = &TetrisFSM::gameplayState;
    controller->setData(this, &left_game, &leftBoard);

    left_game = Tetris(cursen::Vect2(10,22), new UpdateTimerStrategy);
    right_game = Tetris(cursen::Vect2(10,22), new UpdateTimerStrategy);

    leftBoard.initialize();
    leftBoard.setPosition(Vect2(0,0));

    rightBoard.initialize();
    rightBoard.setPosition(leftBoard.getPosition() + Vect2(41, 0));

    leftBoard.getNextBox().setTetromino(left_game.getBlockGenerator()->peekNext());
    leftBoard.getAfterBox().setTetromino(left_game.getBlockGenerator()->peekAfter());
    leftBoard.setGameForm(*this);

    rightBoard.getNextBox().setTetromino(right_game.getBlockGenerator()->peekNext());
    rightBoard.getAfterBox().setTetromino(right_game.getBlockGenerator()->peekAfter());
    rightBoard.setGameForm(*this);

    leftBoard.setField(left_game.getField(), left_game.getSize());
    rightBoard.setField(right_game.getField(), right_game.getSize());

    left_meter.initialize();
    left_meter.setPosition(Vect2(34,2));

    right_meter.initialize();
    right_meter.setPosition(Vect2(38,2));

    onUpdate([this]() { this->inputState->update(*this); });

    onArrowPress([this](EVENT_ARG) {
        if (event.arrowPress.right)
        {
            inputState->pressRight(*this);
        }
        else if (event.arrowPress.left)
        {
            inputState->pressLeft(*this);
        }
        else if (event.arrowPress.down)
        {
            inputState->pressDrop(*this);
        }
    });

    onKeyPress([this](EVENT_ARG) {
        if (event.key.code == ' ')
        {
            left_game.rotateLeft();
        }
        leftBoard.setField(left_game.getField(), left_game.getSize());
    });
}

void GameForm::update()
{
    int update_result = left_game.update();
    if (update_result > 0)
    {
        drop(left_game, leftBoard, update_result);
    }
    update_result = right_game.update();
    if (update_result > 0)
    {
        drop(right_game, rightBoard, update_result);
    }
}

void GameForm::pause()
{

}

void GameForm::drop(Tetris& game, TetrisBoard& board, int amount)
{
    for (int i = 0; i < amount; ++i)
    {
        DropResult result = game.drop();
        if (result.nextPiece)
        {
            if (result.rowsToClear[0] != -1)
            {
                board.runClearRowAnimation(result, game, amount - 1 - i);
                inputState = &TetrisFSM::animationState;
                return;
            }
            else
            {
                game.spawnNextBlock();
                board.getNextBox().setTetromino(game.getBlockGenerator()->peekNext());
                board.getAfterBox().setTetromino(game.getBlockGenerator()->peekAfter());
            }
        }
    }
    board.setField(game.getField(), game.getSize());
}

void GameForm::pressLeft(Tetris& game, TetrisBoard& board)
{
    game.moveLeft();
    board.setField(game.getField(), game.getSize());
}

void GameForm::pressRight(Tetris& game, TetrisBoard& board)
{
    game.moveRight();
    board.setField(game.getField(), game.getSize());
}

void GameForm::clearRows(Tetris& game, TetrisBoard& board, DropResult& dropResult)
{
    game.clearRows(dropResult);
    game.spawnNextBlock();
    board.getNextBox().setTetromino(game.getBlockGenerator()->peekNext());
    board.getAfterBox().setTetromino(game.getBlockGenerator()->peekAfter());
    board.setField(game.getField(), game.getSize());
    inputState = &TetrisFSM::gameplayState;
}

