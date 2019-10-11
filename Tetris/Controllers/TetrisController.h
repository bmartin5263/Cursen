//
// Created by Brandon Martin on 10/8/19.
//

#ifndef CURSEN_TETRISCONTROLLER_H
#define CURSEN_TETRISCONTROLLER_H


class GameForm;
class TetrisController
{

public:

    void setGameForm(GameForm* form) { this->gameForm = form; }

    virtual void pressDrop() = 0;
    virtual void pressLeft() = 0;
    virtual void pressRight() = 0;

protected:

    GameForm* gameForm;

};


#endif //CURSEN_TETRISCONTROLLER_H
