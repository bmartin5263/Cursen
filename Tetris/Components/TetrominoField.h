//
// Created by Brandon Martin on 10/3/19.
//

#ifndef CURSEN_TETROMINOFIELD_H
#define CURSEN_TETROMINOFIELD_H


#include <Cursen/Components/AggregateComponent.h>
#include <Cursen/Components/BitMap.h>

class Tetromino;
class TetrominoField : public cursen::AggregateComponent
{

public:

    TetrominoField(const cursen::Vect2& size);

    void initialize();

    void setField(chtype** field, const cursen::Vect2& size);
    void setTetromino(const Tetromino& tetromino, const cursen::Vect2& location);

    cursen::Vect2 getScale();

private:

    cursen::BitMap field;

};


#endif //CURSEN_TETROMINOFIELD_H
