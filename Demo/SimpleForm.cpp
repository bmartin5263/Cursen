//
// Created by Brandon Martin on 4/10/19.
//

#include <Cursen/Drawing/CursesManager.h>
#include "SimpleForm.h"
#include "Uno/GameObjects/Card.h"

using namespace cursen;

SimpleForm::SimpleForm() :
        Form(cursen::Vect2(70,33))
{
}

void SimpleForm::initialize()
{
    hello.initialize();
    hello.setText("Button is Pressed");
    hello.setEnabled(false);

    count.initialize();
    count.setPosition(Vect2(0, 10));
    count.setText("Count: 0");

    onKeyDown([this](EVENT_ARG) { keyDown(event); });
    onKeyUp([this](EVENT_ARG) { keyUp(event); });
}

void SimpleForm::keyUp(const Event& event)
{
    hello.setEnabled(false);
}

void SimpleForm::keyDown(const Event& event)
{
    static int cnt = 0;
    hello.setEnabled(true);
    count.setText("Count: " + std::to_string(++cnt));
}

