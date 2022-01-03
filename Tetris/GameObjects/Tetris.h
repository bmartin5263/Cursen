//
// Created by Brandon Martin on 9/28/19.
//

#ifndef CURSEN_TETRIS_H
#define CURSEN_TETRIS_H

#include <Cursen/Drawing/Vect2.h>
#include <Tetris/GameObjects/Tetromino.h>
#include <ncurses.h>
#include <Tetris/Utilities/BlockGenerator.h>
#include <Tetris/Utilities/DropResult.h>
#include "Tetris/Components/TetrisBoard.h"
#include "Tetris/Utilities/ClearRowAnimation.h"

class UpdateStrategy;

class Tetris
{

public:

    typedef chtype** Board;

    Tetris() = default;
    Tetris(const cursen::Vect2& size, UpdateStrategy* update_strategy, TetrisBoard* board);

    void reset();
    void clearRows(DropResult& result);
    void checkForRowClears(DropResult& result);
    void spawnNextBlock();

    int update();
    void updateField();
    void pause();

    DropResult drop();
    DropResult fall();
    bool canDrop();

    void moveLeft();
    bool canMoveLeft();

    void moveRight();
    bool canMoveRight();

    void rotateRight();
    bool canRotateRight();

    void rotateLeft();
    bool canRotateLeft();

    void runClearRowAnimation(const DropResult& result, int remainingDrops, const std::function<void()>& onComplete);

    bool canPlaceBlock(const Tetromino* block, const cursen::Vect2& offset);

    Board getField();
    TetrisBoard& getBoard();
    cursen::Vect2 getSize();
    cursen::Vect2 getBlockPosition();
    BlockGenerator* getBlockGenerator();

private:

    bool privCanDrop();
    bool privCanRotateRight();
    bool privCanRotateLeft();
    bool privCanMoveRight();
    bool privCanMoveLeft();

    static void clearRow(chtype* row, int len);
    static bool contains(std::array<int, 4>& rows_to_clear, int val);

    static const chtype BLANK;
    static const chtype BLOCKED;
    static const cursen::Vect2 SPAWN_POSITION;
    static const cursen::Vect2 GHOST_POSITION;
    static const cursen::Vect2 LEFT_OFFSET;
    static const cursen::Vect2 RIGHT_OFFSET;
    static const cursen::Vect2 DOWN_OFFSET;

    void removeBlock();
    void placeBlock();
    void placeGhost();
    void updateGhost();

    Board field;
    TetrisBoard* board;

    const Tetromino* current_block;

    BlockGenerator* block_generator;
    UpdateStrategy* update_strategy;
    ClearRowAnimation clearRowAnimation;

    cursen::Vect2 size;
    cursen::Vect2 position;
    cursen::Vect2 ghost_position;

};
#endif //CURSEN_TETRIS_H
