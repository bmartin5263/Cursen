//
// Created by Brandon Martin on 10/12/19.
//

#include "ClearRowAnimation.h"
#include "Tetris/Forms/GameForm.h"
#include <Tetris/Components/TetrisBoard.h>
#include <Cursen/Drawing/CursesManager.h>

using namespace cursen;

ClearRowAnimation::ClearRowAnimation(TetrisBoard& board) :
    board(board), remainingDrops(0), running(false)
{
}

void ClearRowAnimation::run(const DropResult& result, Tetris& game, int remainingDrops)
{
    CursesManager::Write(std::to_string(result.rowsToClear[0]), 0, 10);
    CursesManager::Write(std::to_string(result.rowsToClear[1]), 0, 11);
    CursesManager::Write(std::to_string(result.rowsToClear[2]), 0, 12);
    CursesManager::Write(std::to_string(result.rowsToClear[3]), 0, 13);
    this->game = &game;
    this->result = result;
    this->col_offset = 0;
    this->row_offset = 0;
    this->running = true;
    this->remainingDrops = remainingDrops;
    this->update();
}

void ClearRowAnimation::update()
{
    if (col_offset != 5)
    {
        int row_num = result.rowsToClear[row_offset++];
        int left = 4 - col_offset;
        int right = 5 + col_offset;
        board.getField()[row_num][left] = ' ' | ColorPair(Color::BLACK, Color::MAGENTA);
        board.getField()[row_num][right] = ' ' | ColorPair(Color::BLACK, Color::MAGENTA);

        if (row_offset == 4 || result.rowsToClear[row_offset] == -1)
        {
            ++col_offset;
            row_offset = 0;
        }
        alarmHandle = AlarmManager::SetTimeout([this]() { this->update(); }, .07);
    }
    else
    {
        board.getGameForm()->clearRows(*game, board, result);
    }
}
