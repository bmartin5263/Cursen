//
// Created by Brandon Martin on 9/28/19.
//

#ifndef CURSEN_TETRIS_H
#define CURSEN_TETRIS_H

#include <Cursen/Drawing/Vect2.h>
#include <Tetris/Components/Tetromino.h>
#include <ncurses.h>
#include <Tetris/Utilities/BlockGenerator.h>

class Tetris
{

public:

    Tetris() = default;
    Tetris(const cursen::Vect2 size);

    void reset();

    bool update();

    void drop();
    bool canDrop();

    void moveLeft();
    bool canMoveLeft();

    void moveRight();
    bool canMoveRight();

    void rotateRight();
    bool canRotateRight();

    void rotateLeft();
    bool canRotateLeft();

    bool canPlaceBlock(const Tetromino* block, const cursen::Vect2& offset);

    chtype** getField();
    cursen::Vect2 getSize();
    cursen::Vect2 getBlockPosition();

private:

    static chtype BLANK;
    static chtype BLOCKED;

    void removeBlock();
    void placeBlock();

    chtype** field;
    const Tetromino* current_block;

    BlockGenerator* block_generator;

    cursen::Vect2 size;
    cursen::Vect2 block_pos;


};
#endif //CURSEN_TETRIS_H
