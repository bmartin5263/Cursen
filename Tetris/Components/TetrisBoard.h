//
// Created by Brandon Martin on 9/28/19.
//

#ifndef CURSEN_TETRISBOARD_H
#define CURSEN_TETRISBOARD_H


#include <Cursen/Components/AggregateComponent.h>
#include <Cursen/Components/Box.h>
#include <Cursen/Components/BitMap.h>
#include "TetrominoField.h"
#include "BlockBox.h"
#include "Tetris/Utilities/DropResult.h"

class GameForm;
class TetrisBoard : public cursen::AggregateComponent
{

public:

    TetrisBoard();

    void initialize() override;
    void setField(chtype** field, const cursen::Vect2& size);

    cursen::Vect2 getScale();
    TetrominoField& getField();

    BlockBox& getNextBox() { return this->next; };
    BlockBox& getAfterBox() { return this->after; };

private:

    cursen::Box border;
    cursen::Box upper_boarder;
    TetrominoField tetrominoField;
    BlockBox next;
    BlockBox after;

};


#endif //CURSEN_TETRISBOARD_H
