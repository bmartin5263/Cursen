//
// Created by Brandon Martin on 10/3/19.
//

#include "TetrominoField.h"
#include "Cursen/Drawing/Content.h"
#include "Tetris/GameObjects/Tetromino.h"

using namespace cursen;

TetrominoField::TetrominoField(const Vect2& size)
{
    field.setSize(size);
}

void TetrominoField::initialize()
{
    field.initialize();
    field.setScale(Vect2(2,1));
    addRelative(field);
}

void TetrominoField::setField(chtype** field, const cursen::Vect2& size)
{
    for (int y = 0; y < size.y; ++y)
    {
        for (int x = 0; x < size.x; ++x)
        {
            if (y < 2 && (x < 2 || x > 6))
            {
                this->field[y][x] = Content::TRANSPARENT;
            }
            else
            {
                this->field[y][x] = field[y][x];
            }
        }
    }
}

void TetrominoField::setTetromino(const Tetromino* tetromino, const cursen::Vect2& location)
{
    Vect2 size = field.getSize();
    for (int y = 0; y < size.y; ++y)
    {
        for (int x = 0; x < size.x; ++x)
        {
            this->field[y][x] = Content::TRANSPARENT;
        }
    }
    chtype** body = field.getUnscaledContent().getText();
    tetromino->placeOnto(body, location);
}

cursen::Vect2 TetrominoField::getScale()
{
    return field.getScale();
}
