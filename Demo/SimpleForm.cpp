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
    back.initialize();
    back.setPosition(Vect2(0,0));
    back.injectCard(Card(CardColor::RED, CardValue::TWO), false);

    front.initialize();
    front.setPosition(Vect2(3,3));
    front.injectCard(Card(CardColor::BLUE, CardValue::ONE), false);

    back.onEnterPress([this](const cursen::Event& event) { front.drawOnTopOf(back); });
}

