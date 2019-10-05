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
const Vect2 Tetris::LEFT_OFFSET = Vect2(-1, 0);
const Vect2 Tetris::RIGHT_OFFSET = Vect2(1, 0);
const Vect2 Tetris::DOWN_OFFSET = Vect2(0, 1);

Tetris::Tetris(const cursen::Vect2 size, UpdateStrategy* update_strategy) :
    field(new chtype*[size.y]), current_block(nullptr), block_generator(new BlockGenerator), update_strategy(update_strategy),
    size(size), position(SPAWN_POSITION)
{
    current_block = &block_generator->next();
    for (int y = 0; y < size.y; ++y)
    {
        this->field[y] = new chtype[size.x];
        for (int x = 0; x < size.x; ++x) this->field[y][x] = BLANK;
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
    bool can_drop = privCanDrop();
    if (can_drop)
    {
        this->position += DOWN_OFFSET;
        update_strategy->reset();
    }
    placeBlock();
    if (!can_drop)
    {
        // New Block
        clearRows();
        this->current_block = &block_generator->next();
        this->position = SPAWN_POSITION;
        this->update_strategy->reset();
        placeBlock();
    }
}

bool Tetris::canDrop()
{
    removeBlock();
    bool result = canPlaceBlock(current_block, position + Vect2(0,1));
    placeBlock();
    return result;
}

bool Tetris::canPlaceBlock(const Tetromino* block, const cursen::Vect2& offset)
{
    for (auto& pair : block->body())
    {
        Vect2 new_pos = pair + offset;
        if (new_pos.x < 0 || new_pos.x >= size.x || new_pos.y < 0 || new_pos.y >= size.y || field[new_pos.y][new_pos.x] != BLANK
                || (new_pos.y < 2 && (new_pos.x < 2 || new_pos.x > 6))) return false;
    }
    return true;
}

void Tetris::moveLeft()
{
    removeBlock();
    if (privCanMoveLeft())
    {
        this->position += LEFT_OFFSET;
    }
    placeBlock();
}

bool Tetris::canMoveLeft()
{
    removeBlock();
    bool result = canPlaceBlock(current_block, LEFT_OFFSET + position);
    placeBlock();
    return result;
}

void Tetris::moveRight()
{
    removeBlock();
    if (privCanMoveRight())
    {
        this->position += RIGHT_OFFSET;
    }
    placeBlock();
}

bool Tetris::canMoveRight()
{
    removeBlock();
    bool result = canPlaceBlock(current_block, RIGHT_OFFSET + position);
    placeBlock();
    return result;
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
    if (privCanRotateRight())
    {
        this->current_block = &current_block->rotateRight();
    }
    placeBlock();
}

bool Tetris::canRotateRight()
{
    removeBlock();
    bool result = canPlaceBlock(&current_block->rotateRight(), position);
    placeBlock();
    return result;
}

void Tetris::rotateLeft()
{
    removeBlock();
    if (privCanRotateLeft())
    {
        this->current_block = &current_block->rotateLeft();
    }
    placeBlock();
}

bool Tetris::canRotateLeft()
{
    removeBlock();
    bool result = canPlaceBlock(&current_block->rotateLeft(), position);
    placeBlock();
    return result;
}

cursen::Vect2 Tetris::getBlockPosition()
{
    return position;
}

BlockGenerator* Tetris::getBlockGenerator()
{
    return block_generator;
}

bool Tetris::privCanDrop()
{
    return canPlaceBlock(current_block, position + DOWN_OFFSET);
}

bool Tetris::privCanRotateRight()
{
    return canPlaceBlock(&current_block->rotateRight(), position);
}

bool Tetris::privCanRotateLeft()
{
    return canPlaceBlock(&current_block->rotateLeft(), position);
}

bool Tetris::privCanMoveRight()
{
    return canPlaceBlock(current_block, RIGHT_OFFSET + position);
}

bool Tetris::privCanMoveLeft()
{
    return canPlaceBlock(current_block, LEFT_OFFSET + position);
}

void Tetris::clearRows()
{
    // Check if each block contributed to row clearing
    for (auto& block : current_block->body())
    {
        int block_row = block.y + position.y;
        bool can_be_cleared = true;
        for (int i = 0; i < size.x; ++i)
        {
            if (field[block_row][i] == Tetris::BLANK) {
                can_be_cleared = false;
                break;
            }
        }
        if (can_be_cleared)
        {
            // Clear the row and bubble it to the top
            clearRow(field[block_row], size.x);
            for (int y = block_row - 1; y >= 0; --y)
            {
                chtype* temp = field[y];
                field[y] = field[y+1];
                field[y+1] = temp;
            }
        }
    }
}

void Tetris::clearRow(chtype* row, int len)
{
    for (int i = 0; i < len; ++i) row[i] = Tetris::BLANK;
}

