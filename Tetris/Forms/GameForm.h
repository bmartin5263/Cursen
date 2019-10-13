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

class InputState;
class TetrisController;
class GameForm : public cursen::Form
{
public:

    GameForm();

    void initialize() override;
    void update();

    void pause();

    void fall(Tetris& game, TetrisBoard& board);
    void drop(Tetris& game, TetrisBoard& board, int amount);
    void pressLeft(Tetris& game, TetrisBoard& board);
    void pressRight(Tetris& game, TetrisBoard& board);
    void clearRows(Tetris& game, TetrisBoard& board, DropResult& dropResult);

    TetrisController& getController() const { return *this->controller; }

private:

    TetrisBoard leftBoard;
    TetrisBoard rightBoard;

    TetrisController* controller;
    const InputState* inputState;

    Tetris left_game;
    Tetris right_game;

    BoardMeter left_meter;
    BoardMeter right_meter;

    cursen::Label left_pause_label;
    cursen::Label right_pause_label;

    bool is_paused;
};


#endif //CURSEN_GAMEFORM_H
