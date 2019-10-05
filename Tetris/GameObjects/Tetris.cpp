//
// Created by Brandon Martin on 9/28/19.
//

#include <Cursen/Drawing/Color.h>
#include <Cursen/Drawing/ColorPair.h>
#include <Cursen/Drawing/Content.h>
#include "Tetris/Utilities/UpdateStrategy.h"
#include "Tetris.h"

using namespace cursen;

const chtype Tetris::BLANK = ' ';
const chtype Tetris::BLOCKED = 'X';
const Vect2 Tetris::SPAWN_POSITION = Vect2(3, 0);

Tetris::Tetris(const cursen::Vect2 size, UpdateStrategy* update_strategy) :
    field(new chtype*[size.y]), current_block(nullptr), block_generator(new BlockGenerator), update_strategy(update_strategy),
    size(size), position(SPAWN_POSITION)
{
    current_block = block_generator->next();
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
    return update_strategy->update(*this);
}

Tetris::Board Tetris::getField()
{
    return this->field;
}

cursen::Vect2 Tetris::getSize()
{
    return this->size;
}

void Tetris::removeBlock()
{
    current_block->removeFrom(field, position, BLANK);
}

void Tetris::placeBlock()
{
    current_block->placeOnto(field, position);
}

void Tetris::drop()
{
    removeBlock();
    bool can_drop = canDrop();
    if (can_drop)
    {
        this->position += Vect2(0, 1);
        update_strategy->reset();
    }
    placeBlock();
    if (!can_drop)
    {
        this->current_block = block_generator->next();
        this->position = Vect2(3,0);
        this->update_strategy->reset();
        placeBlock();
    }
}

bool Tetris::canDrop()
{
    return canPlaceBlock(current_block, position + Vect2(0,1));
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
        this->position += Vect2(-1, 0);
    }
    placeBlock();
}

bool Tetris::canMoveLeft()
{
    return canPlaceBlock(current_block, Vect2(-1, 0) + position);
}

void Tetris::moveRight()
{
    removeBlock();
    if (canMoveRight())
    {
        this->position += Vect2(1, 0);
    }
    placeBlock();
}

bool Tetris::canMoveRight()
{
    return canPlaceBlock(current_block, Vect2(1, 0) + position);
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
    return canPlaceBlock(&current_block->rotateRight(), position);
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
    return canPlaceBlock(&current_block->rotateLeft(), position);
}

cursen::Vect2 Tetris::getBlockPosition()
{
    return position;
}

BlockGenerator* Tetris::getBlockGenerator()
{
    return block_generator;
}

