//
// Created by Brandon Martin on 9/28/19.
//

#include <Cursen/Drawing/CursesManager.h>
#include "TetrisBoard.h"

using namespace cursen;

TetrisBoard::TetrisBoard()
{

}

void TetrisBoard::initialize()
{
    border.initialize();
    border.setPosition(Vect2(0, 2));
    border.setSize(Vect2(22,22));
    addRelative(border);

    upper_boarder.initialize();
    upper_boarder.setPosition(Vect2(4, 0));
    upper_boarder.setSize(Vect2(12, 3));
    upper_boarder.setLower(' ');
    upper_boarder.setLowerRight(CursesManager::LLCORNER);
    upper_boarder.setLowerLeft(CursesManager::LRCORNER);
    addRelative(upper_boarder);

    field.initialize();
    field.setSize(Vect2(10,22));
    field.setScale(Vect2(2,1));
    field.setPosition(Vect2(1,1));
    addRelative(field);

//    field[0][0] = ' ' | ColorPair(Color::WHITE, Color::MAGENTA);
//    field[0][1] = ' ' | ColorPair(Color::WHITE, Color::MAGENTA);
//    field[0][2] = ' ' | ColorPair(Color::WHITE, Color::MAGENTA);
//    field[0][3] = ' ' | ColorPair(Color::WHITE, Color::BLUE);
//    field[0][4] = ' ' | ColorPair(Color::WHITE, Color::MAGENTA);
//    field[0][5] = ' ' | ColorPair(Color::WHITE, Color::MAGENTA);
//    field[0][6] = ' ' | ColorPair(Color::WHITE, Color::MAGENTA);
//    field[0][7] = ' ' | ColorPair(Color::WHITE, Color::MAGENTA);
//    field[0][8] = ' ' | ColorPair(Color::WHITE, Color::MAGENTA);
//    field[0][9] = ' ' | ColorPair(Color::WHITE, Color::MAGENTA);
}

void TetrisBoard::setField(chtype** field, const cursen::Vect2& size)
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

cursen::Vect2 TetrisBoard::getScale()
{
    return field.getScale();
}
