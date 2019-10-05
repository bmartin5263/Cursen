//
// Created by Brandon Martin on 9/28/19.
//

#ifndef CURSEN_TETRIS_H
#define CURSEN_TETRIS_H

#include <Cursen/Drawing/Vect2.h>
#include <Tetris/GameObjects/Tetromino.h>
#include <ncurses.h>
#include <Tetris/Utilities/BlockGenerator.h>

class UpdateStrategy;

class Tetris
{

public:

    typedef chtype** Board;

    Tetris() = default;
    Tetris(const cursen::Vect2 size, UpdateStrategy* update_strategy);

    void reset();
    void clearRows();

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

    Board getField();
    cursen::Vect2 getSize();
    cursen::Vect2 getBlockPosition();
    BlockGenerator* getBlockGenerator();

private:

    bool privCanDrop();
    bool privCanRotateRight();
    bool privCanRotateLeft();
    bool privCanMoveRight();
    bool privCanMoveLeft();

    static const chtype BLANK;
    static const chtype BLOCKED;
    static const cursen::Vect2 SPAWN_POSITION;
    static const cursen::Vect2 LEFT_OFFSET;
    static const cursen::Vect2 RIGHT_OFFSET;
    static const cursen::Vect2 DOWN_OFFSET;
    static void clearRow(chtype* row, int len);

    void removeBlock();
    void placeBlock();

    Board field;
    const Tetromino* current_block;

    BlockGenerator* block_generator;
    UpdateStrategy* update_strategy;

    cursen::Vect2 size;
    cursen::Vect2 position;


};
#endif //CURSEN_TETRIS_H
