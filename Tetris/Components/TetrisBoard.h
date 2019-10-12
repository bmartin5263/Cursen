//
// Created by Brandon Martin on 9/28/19.
//

#ifndef CURSEN_TETRISBOARD_H
#define CURSEN_TETRISBOARD_H


#include <Cursen/Components/AggregateComponent.h>
#include <Cursen/Components/Box.h>
#include <Cursen/Components/BitMap.h>
#include <Tetris/Utilities/ClearRowAnimation.h>
#include "TetrominoField.h"
#include "BlockBox.h"

class Tetris;
class GameForm;
class TetrisBoard : public cursen::AggregateComponent
{

public:

    TetrisBoard();

    void initialize() override;
    void setField(chtype** field, const cursen::Vect2& size);
    void runClearRowAnimation(const DropResult& result, Tetris& game, int remainingDrops);

    cursen::Vect2 getScale();
    TetrominoField& getField();

    void setGameForm(GameForm& gameForm) { this->gameForm = &gameForm; };
    GameForm* getGameForm() const { return this->gameForm; };

    BlockBox& getNextBox() { return this->next; };
    BlockBox& getAfterBox() { return this->after; };


private:

    GameForm* gameForm;


    cursen::Box border;
    cursen::Box upper_boarder;
    TetrominoField tetrominoField;
    BlockBox next;
    BlockBox after;

    ClearRowAnimation clearRowAnimation;

};


#endif //CURSEN_TETRISBOARD_H
