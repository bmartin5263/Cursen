//
// Created by Brandon Martin on 9/25/19.
//

#include <Tetris/GameObjects/Tetris.h>
#include "GameForm.h"

using namespace cursen;

GameForm::GameForm() : Form(Vect2(70,70))
{}

void GameForm::initialize()
{
    Tetromino::InitializeGraphics();
    leftBoard.initialize();

    rightBoard.initialize();
    rightBoard.setPosition(Vect2(22, 0));

    x.initialize();
    x.setText("XX");
    x.setHidden(true);
    x.setForeground(Color::BLACK);
    x.setBackground(Color::BLUE);
    x.setDrawOrder(100);
    x.setPosition(left_game.getBlockPosition() * leftBoard.getScale() + Vect2(1,3));

    left_game = Tetris(cursen::Vect2(10,22));
    right_game = Tetris(cursen::Vect2(10,22));

    leftBoard.setField(left_game.getField(), left_game.getSize());

    onUpdate([this]() { this->update(); });
    onArrowPress([this](EVENT_ARG) {
        if (event.arrowPress.right)
        {
            left_game.moveRight();
        }
        else if (event.arrowPress.left)
        {
            left_game.moveLeft();
        }
        else if (event.arrowPress.down)
        {
            left_game.drop();
        }
        x.setPosition(left_game.getBlockPosition() * leftBoard.getScale() + Vect2(1,3));
        leftBoard.setField(left_game.getField(), left_game.getSize());
    });
    onKeyPress([this](EVENT_ARG) {
        if (event.key.code == ' ')
        {
            left_game.rotateLeft();
        }
        x.setPosition(left_game.getBlockPosition() * leftBoard.getScale() + Vect2(1,3));
        leftBoard.setField(left_game.getField(), left_game.getSize());
    });
}

void GameForm::update()
{
    if (left_game.update())
    {
        leftBoard.setField(left_game.getField(), left_game.getSize());
    }
    if (right_game.update())
    {

    }
}

