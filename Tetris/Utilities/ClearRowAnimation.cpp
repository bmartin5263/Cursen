//
// Created by Brandon Martin on 10/12/19.
//

#include "ClearRowAnimation.h"
#include "Tetris/Forms/GameForm.h"
#include <Tetris/Components/TetrisBoard.h>
#include <Tetris/GameObjects/Tetris.h>
#include <Cursen/Drawing/TerminalManager.h>

using namespace cursen;

void ClearRowAnimation::run(const DropResult& result, Tetris* game, int remainingDrops, const std::function<void()>& onComplete)
{
    this->game = game;
    this->result = result;
    this->col_offset = 0;
    this->row_offset = 0;
    this->remainingDrops = remainingDrops;
    this->onComplete = onComplete;
    this->update();
}

void ClearRowAnimation::update()
{
    if (col_offset != 5) {
        int row_num = result.rowsToClear[row_offset++];
        int left = 4 - col_offset;
        int right = 5 + col_offset;
        game->getBoard().getField()[row_num][left] = ' ' | ColorPair(Color::BLACK, Color::MAGENTA);
        game->getBoard().getField()[row_num][right] = ' ' | ColorPair(Color::BLACK, Color::MAGENTA);

        if (row_offset == 4 || result.rowsToClear[row_offset] == -1) {
            ++col_offset;
            row_offset = 0;
        }
        alarmHandle = AlarmManager::SetTimeout([this]() { this->update(); }, .07);
    }
    else {
        onComplete();
    }
}
