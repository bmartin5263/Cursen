//
// Created by Brandon Martin on 9/28/19.
//

#include <Cursen/Drawing/CursesManager.h>
#include "TetrisBoard.h"

using namespace cursen;

TetrisBoard::TetrisBoard() :
    tetrominoField(Vect2(10,22)), clearRowAnimation(*this)
{

}

void TetrisBoard::initialize()
{
    border.initialize();
    border.setPosition(Vect2(12, 2));
    border.setSize(Vect2(22,22));
    addRelative(border);

    next.initialize();
    next.setPosition(Vect2(0,6));
    next.setText("Next");
    addRelative(next);

    after.initialize();
    after.setPosition(Vect2(0,2));
    after.setText("After");
    addRelative(after);

    upper_boarder.initialize();
    upper_boarder.setPosition(Vect2(16, 0));
    upper_boarder.setSize(Vect2(12, 3));
    upper_boarder.setLower(' ');
    upper_boarder.setLowerRight(CursesManager::LLCORNER);
    upper_boarder.setLowerLeft(CursesManager::LRCORNER);
    addRelative(upper_boarder);

    tetrominoField.initialize();
    tetrominoField.setPosition(Vect2(13,1));
    addRelative(tetrominoField);

}

void TetrisBoard::setField(chtype** field, const cursen::Vect2& size)
{
    tetrominoField.setField(field, size);
}

cursen::Vect2 TetrisBoard::getScale()
{
    return tetrominoField.getScale();
}

TetrominoField& TetrisBoard::getField()
{
    return tetrominoField;
}

void TetrisBoard::runClearRowAnimation(const DropResult& result, Tetris& game, int remainingDrops)
{
    clearRowAnimation.run(result, game, remainingDrops);
}
