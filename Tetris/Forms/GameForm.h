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

class GameForm : public cursen::Form
{
public:

    GameForm();

    void initialize() override;
    void update();

private:

    TetrisBoard leftBoard;
    TetrisBoard rightBoard;

    Tetris left_game;
    Tetris right_game;

    cursen::Label x;
    cursen::Box box;
    cursen::Box box2;
    cursen::Box next_box_1;
    cursen::Box next_box_2;
    cursen::BitMap next_bitmap_1;

};


#endif //CURSEN_GAMEFORM_H
