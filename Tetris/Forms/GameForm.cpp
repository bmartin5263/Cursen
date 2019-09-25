//
// Created by Brandon Martin on 9/25/19.
//

#include "GameForm.h"

using namespace cursen;

GameForm::GameForm() : Form(Vect2(70,70))
{}

void GameForm::initialize()
{
    bitmap.initialize();
    bitmap.setSize(Vect2(4,4));

    bitmap[0][0] = ' ' | ColorPair(Color::WHITE, Color::MAGENTA);
    bitmap[0][1] = ' ' | ColorPair(Color::WHITE, Color::GREEN);
    bitmap[1][0] = ' ' | ColorPair(Color::WHITE, Color::BLUE);
    bitmap[1][1] = ' ' | ColorPair(Color::WHITE, Color::YELLOW);

    bitmap.setScale(Vect2(2,1));

    onAnyKeyPress([this](EVENT_ARG) {
        switch (event.key.code)
        {
            case '+':
                bitmap.setScale(bitmap.getScale() * Vect2(2,2));
                break;
            case '-':
                bitmap.setScale(bitmap.getScale() / Vect2(2,2));
                break;
            case '0':
                bitmap.setSize(bitmap.getSize() * Vect2(2,2));
            default:
                break;
        }
    });
}

