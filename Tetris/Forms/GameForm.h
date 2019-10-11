//
// Created by Brandon Martin on 9/25/19.
//

#ifndef CURSEN_GAMEFORM_H
#define CURSEN_GAMEFORM_H


#include <Cursen/Components/Form.h>
#include <Cursen/Components/BitMap.h>
#include <Tetris/Components/TetrisBoard.h>
#include <Tetris/GameObjects/Tetris.h>
#include <Cursen/Components/Label.h>
#include <Tetris/Components/BlockBox.h>
#include <Tetris/Components/BoardMeter.h>

class TetrisController;
class GameForm : public cursen::Form
{
public:

    GameForm();

    void initialize() override;
    void update();

    void drop();

private:

    TetrisBoard leftBoard;
    TetrisBoard rightBoard;

    TetrisController* controller;

    Tetris left_game;
    Tetris right_game;

    BlockBox left_next_block_field;
    BlockBox left_after_block_field;
    BlockBox right_next_block_field;
    BlockBox right_after_block_field;

    BoardMeter left_meter;
    BoardMeter right_meter;

};


#endif //CURSEN_GAMEFORM_H
