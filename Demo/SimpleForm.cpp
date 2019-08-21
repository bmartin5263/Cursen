//
// Created by Brandon Martin on 4/10/19.
//

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
    hello.setPosition(Vect2(0,0));
    hello.setForeground(Color::RED);
    hello.setText("Hello!");
    hello.setLength(30);

    onKeyPress([this](const Event& event) { hello.setText("fuck"); });
}

