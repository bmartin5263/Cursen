//
// Created by Brandon Martin on 9/11/19.
//

#include "SimonForm.h"

using namespace cursen;

SimonForm::SimonForm() : Form(Vect2(25, 15)), colorAnimation(this), requesting_input(false), gameover(false)
{}

void SimonForm::initialize()
{
    border.initialize();
    border.setSize(getSize());
    border.setFill(Content::TRANSPARENT);

    msg.initialize();
    msg.setText("Game Beginning in 3");
    msg.setPosition(Vect2(3, 1));

    level.initialize();
    level.setText("Level: 1");
    level.setPosition(Vect2(1, 13));

    button[0].initialize();
    button[0].setPosition(Vect2(2,2));
    button[0].setText("Blue");
    button[0].setForeground(Color::BLUE);

    button[1].initialize();
    button[1].setPosition(Vect2(13,2));
    button[1].setText("Red ");
    button[1].setForeground(Color::MAGENTA);

    button[2].initialize();
    button[2].setPosition(Vect2(2,7));
    button[2].setText("Yellow");
    button[2].setForeground(Color::YELLOW);

    button[3].initialize();
    button[3].setPosition(Vect2(13,7));
    button[3].setText("Green ");
    button[3].setForeground(Color::GREEN);

    count_down.setVariableTime(false);
    count_down.setFrameDuration(1.0);
    count_down.setInfinite(false);
    count_down.add([this]() { msg.setText("Game Beginning in 2"); });
    count_down.add([this]() { msg.setText("Game Beginning in 1"); });
    count_down.add([this]() { nextRound(); });

    onAnyKeyPress([this](EVENT_ARG) {
        if (requesting_input)
        {
            switch (event.key.code)
            {
                case 'b':
                case 'B':
                    button[0].flash();
                    AlarmManager::SetTimeout([this]() { makeGuess(0); }, .4);
                    break;
                case 'r':
                case 'R':
                    button[1].flash();
                    AlarmManager::SetTimeout([this]() { makeGuess(1); }, .4);
                    break;
                case 'y':
                case 'Y':
                    button[2].flash();
                    AlarmManager::SetTimeout([this]() { makeGuess(2); }, .4);
                    break;
                case 'g':
                case 'G':
                    button[3].flash();
                    AlarmManager::SetTimeout([this]() { makeGuess(3); }, .4);
                    break;
                default:
                    break;
            }
        }
        else if (gameover)
        {
            close(nullptr);
        }
    });

    count_down.start(1.0);
}

void SimonForm::showPattern()
{

}

void SimonForm::nextRound()
{
    requesting_input = false;
    simon.incrementRound();
    level.setText("Level: " + std::to_string(simon.getLevel()));
    msg.setText("Watch Carefully...");
    colorAnimation.start();
}

void SimonForm::flash(int index)
{
    button[index].flash();
}

void SimonForm::startGuessing()
{
    requesting_input = true;
    msg.setText("Repeat the Sequence");
}

void SimonForm::makeGuess(int guess)
{
    bool correct = simon.guess(guess);
    if (!correct)
    {
        msg.setForeground(Color::MAGENTA);
        msg.setText("Game Over");
        requesting_input = false;
        gameover = true;
    }
    else
    {
        if (simon.readyForNextRound())
        {
            nextRound();
        }
    }
}

