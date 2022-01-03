//
// Created by Brandon Martin on 10/8/19.
//

#ifndef CURSEN_TETRISCONTROLLER_H
#define CURSEN_TETRISCONTROLLER_H

#include <cassert>

class Tetris;
class TetrisBoard;
class BlockBox;
class GameForm;
class TetrisController
{

public:

    virtual ~TetrisController() = default;

    void setData(GameForm* form, Tetris* _game)
    {
        assert(_game != nullptr);
        this->gameForm = form;
        this->game = _game;
    }

    virtual void pressDrop() = 0;
    virtual void pressLeft() = 0;
    virtual void pressRight() = 0;
    virtual void pressFall() = 0;

    virtual void handleDrop() = 0;

protected:

    GameForm* gameForm;
    Tetris* game;

};


#endif //CURSEN_TETRISCONTROLLER_H
