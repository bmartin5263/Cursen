//
// Created by Brandon Martin on 10/8/19.
//

#ifndef CURSEN_TETRISCONTROLLER_H
#define CURSEN_TETRISCONTROLLER_H

class Tetris;
class TetrisBoard;
class BlockBox;
class GameForm;
class TetrisController
{

public:

    virtual ~TetrisController() = default;

    void setData(GameForm* form, Tetris* game, TetrisBoard* board)
    {
        this->gameForm = form;
        this->game = game;
        this->board = board;
    }

    virtual void pressDrop() = 0;
    virtual void pressLeft() = 0;
    virtual void pressRight() = 0;

    virtual void handleDrop() = 0;

protected:

    GameForm* gameForm;
    Tetris* game;
    TetrisBoard* board;

};


#endif //CURSEN_TETRISCONTROLLER_H
