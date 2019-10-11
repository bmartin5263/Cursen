//
// Created by Brandon Martin on 9/25/19.
//

#include <Tetris/GameObjects/Tetris.h>
#include <Tetris/Utilities/UpdateTimerStrategy.h>
#include <Tetris/Utilities/NullUpdateStrategy.h>
#include <Tetris/Controllers/Controllers.h>
#include "GameForm.h"

using namespace cursen;

GameForm::GameForm() : Form(Vect2(80,70))
{}

void GameForm::initialize()
{
    Tetromino::InitializeGraphics();

    controller = &Controllers::localTetrisController;
    left_game = Tetris(cursen::Vect2(10,22), new UpdateTimerStrategy);
    right_game = Tetris(cursen::Vect2(10,22), new UpdateTimerStrategy);

    leftBoard.initialize();
    leftBoard.setPosition(Vect2(12,0));

    rightBoard.initialize();
    rightBoard.setPosition(leftBoard.getPosition() + Vect2(29, 0));

    left_next_block_field.initialize();
    left_next_block_field.setPosition(Vect2(0,6));
    left_next_block_field.setText("Next");

    left_after_block_field.initialize();
    left_after_block_field.setPosition(Vect2(0,2));
    left_after_block_field.setText("After");

    right_next_block_field.initialize();
    right_next_block_field.setPosition(Vect2(63,6));
    right_next_block_field.setText("Next");

    right_after_block_field.initialize();
    right_after_block_field.setPosition(Vect2(63,2));
    right_after_block_field.setText("After");

    left_next_block_field.setTetromino(left_game.getBlockGenerator()->peekNext());
    left_after_block_field.setTetromino(left_game.getBlockGenerator()->peekAfter());

    right_next_block_field.setTetromino(right_game.getBlockGenerator()->peekNext());
    right_after_block_field.setTetromino(right_game.getBlockGenerator()->peekAfter());

    leftBoard.setField(left_game.getField(), left_game.getSize());
    rightBoard.setField(right_game.getField(), right_game.getSize());

    left_meter.initialize();
    left_meter.setPosition(Vect2(34,2));

    right_meter.initialize();
    right_meter.setPosition(Vect2(38,2));

    onUpdate([this]() { this->update(); });

    onArrowPress([this](EVENT_ARG) {
        DropResult result;
        if (event.arrowPress.right)
        {
            left_game.moveRight();
        }
        else if (event.arrowPress.left)
        {
            left_game.moveLeft();
        }
        else if (event.arrowPress.down)
        {
            result = left_game.drop();
            if (result.nextPiece)
            {
                left_next_block_field.setTetromino(left_game.getBlockGenerator()->peekNext());
                left_after_block_field.setTetromino(left_game.getBlockGenerator()->peekAfter());
            }
        }
        leftBoard.setField(left_game.getField(), left_game.getSize());
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
    if (left_game.update())
    {
        leftBoard.setField(left_game.getField(), left_game.getSize());
        left_next_block_field.setTetromino(left_game.getBlockGenerator()->peekNext());
        left_after_block_field.setTetromino(left_game.getBlockGenerator()->peekAfter());
    }
    if (right_game.update())
    {
        rightBoard.setField(right_game.getField(), right_game.getSize());
        right_next_block_field.setTetromino(right_game.getBlockGenerator()->peekNext());
        right_after_block_field.setTetromino(right_game.getBlockGenerator()->peekAfter());
    }
}

