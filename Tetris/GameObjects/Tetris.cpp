//
// Created by Brandon Martin on 9/28/19.
//

#include <Cursen/Drawing/Color.h>
#include <Cursen/Drawing/ColorPair.h>
#include <Cursen/Drawing/Content.h>
#include "Tetris.h"

using namespace cursen;

chtype Tetris::BLANK = ' ';
chtype Tetris::BLOCKED = 'X';

Tetris::Tetris(const cursen::Vect2 size) :
    size(size)
{
    block_generator = new BlockGenerator;
    this->current_block = &Tetromino::T_0;
    this->block_pos = Vect2(3,0);
    this->field = new chtype*[size.y];
    for (int y = 0; y < size.y; ++y)
    {
        this->field[y] = new chtype[size.x];
        for (int x = 0; x < size.x; ++x) this->field[y][x] = BLANK;
    }
    for (int y = 0; y < 2; ++y)
    {
        this->field[y][0] = Content::TRANSPARENT;
        this->field[y][1] = Content::TRANSPARENT;
        this->field[y][7] = Content::TRANSPARENT;
        this->field[y][8] = Content::TRANSPARENT;
        this->field[y][9] = Content::TRANSPARENT;
    }

    placeBlock();
}

bool Tetris::update()
{
    return false;
}

chtype** Tetris::getField()
{
    return this->field;
}

cursen::Vect2 Tetris::getSize()
{
    return this->size;
}

void Tetris::removeBlock()
{
    for (auto& pair : current_block->body())
    {
        field[block_pos.y + pair.y][block_pos.x + pair.x] = BLANK;
    }
}

void Tetris::placeBlock()
{
    for (auto& pair : current_block->body())
    {
        field[block_pos.y + pair.y][block_pos.x + pair.x] = current_block->getGraphic();
    }
    //field[block_pos.y][block_pos.x] = 'X' | Tetromino::CYAN_BLOCK;
}

void Tetris::drop()
{
    removeBlock();
    if (canDrop())
    {
        this->block_pos += Vect2(0, 1);
    }
    placeBlock();
}

bool Tetris::canDrop()
{
    return canPlaceBlock(current_block, block_pos + Vect2(0,1));
}

bool Tetris::canPlaceBlock(const Tetromino* block, const cursen::Vect2& offset)
{
    for (auto& pair : block->body())
    {
        Vect2 new_pos = pair + offset;
        if (new_pos.x < 0 || new_pos.x >= size.x || new_pos.y < 0 || new_pos.y >= size.y || field[new_pos.y][new_pos.x] != BLANK) return false;
    }
    return true;
}

void Tetris::moveLeft()
{
    removeBlock();
    if (canMoveLeft())
    {
        this->block_pos += Vect2(-1, 0);
    }
    placeBlock();
}

bool Tetris::canMoveLeft()
{
    return canPlaceBlock(current_block, Vect2(-1, 0) + block_pos);
}

void Tetris::moveRight()
{
    removeBlock();
    if (canMoveRight())
    {
        this->block_pos += Vect2(1, 0);
    }
    placeBlock();
}

bool Tetris::canMoveRight()
{
    return canPlaceBlock(current_block, Vect2(1, 0) + block_pos);
}

void Tetris::reset()
{
    this->current_block = nullptr;
    for (int y = 0; y < size.y; ++y)
    {
        for (int x = 0; x < size.x; ++x)
        {
            field[y][x] = BLANK;
        }
    }
}

void Tetris::rotateRight()
{
    removeBlock();
    if (canRotateRight())
    {
        this->current_block = &current_block->rotateRight();
    }
    placeBlock();
}

bool Tetris::canRotateRight()
{
    return canPlaceBlock(&current_block->rotateRight(), block_pos);
}

void Tetris::rotateLeft()
{
    removeBlock();
    if (canRotateLeft())
    {
        this->current_block = &current_block->rotateLeft();
    }
    placeBlock();
}

bool Tetris::canRotateLeft()
{
    return canPlaceBlock(&current_block->rotateLeft(), block_pos);
}

cursen::Vect2 Tetris::getBlockPosition()
{
    return block_pos;
}

