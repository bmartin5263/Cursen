//
// Created by Brandon Martin on 9/25/19.
//

#include <Tetris/GameObjects/Tetris.h>
#include <Tetris/Utilities/UpdateTimerStrategy.h>
#include <Tetris/Utilities/NullUpdateStrategy.h>
#include "GameForm.h"

using namespace cursen;

GameForm::GameForm() : Form(Vect2(70,70))
{}

void GameForm::initialize()
{
    Tetromino::InitializeGraphics();
    leftBoard.initialize();
    leftBoard.setPosition(Vect2(12,0));

    rightBoard.initialize();
    rightBoard.setPosition(leftBoard.getPosition() + Vect2(29, 0));

    box.initialize();
    box.setPosition(leftBoard.getPosition() + Vect2(22,2));
    box.setSize(Vect2(3,22));

    box2.initialize();
    box2.setPosition(leftBoard.getPosition() + Vect2(26,2));
    box2.setSize(Vect2(3,22));

    next_box_1.initialize();
    next_box_1.setPosition(Vect2(0,2));
    next_box_1.setSize(Vect2(12, 4));

    next_bitmap_1.initialize();
    next_bitmap_1.setSize(Vect2(10,2));
    next_bitmap_1.setPosition(next_box_1.getPosition() + Vect2(1,1));
    next_bitmap_1.drawOnTopOf(next_box_1);
    next_bitmap_1.setScale(Vect2(2,1));
    next_bitmap_1[0][1] = ' ' | ColorPair(Color::BLACK, Color::BLUE);
    next_bitmap_1[0][2] = ' ' | ColorPair(Color::BLACK, Color::BLUE);
    next_bitmap_1[0][3] = ' ' | ColorPair(Color::BLACK, Color::BLUE);
    next_bitmap_1[1][3] = ' ' | ColorPair(Color::BLACK, Color::BLUE);

    x.initialize();
    x.setText("XX");
    x.setHidden(true);
    x.setForeground(Color::BLACK);
    x.setBackground(Color::BLUE);
    x.setDrawOrder(100);
    x.setPosition(left_game.getBlockPosition() * leftBoard.getScale() + Vect2(1,3));

    left_game = Tetris(cursen::Vect2(10,22), new UpdateTimerStrategy);
    right_game = Tetris(cursen::Vect2(10,22), new UpdateTimerStrategy);

    leftBoard.setField(left_game.getField(), left_game.getSize());
    rightBoard.setField(right_game.getField(), right_game.getSize());

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
        rightBoard.setField(right_game.getField(), right_game.getSize());
    }
}

