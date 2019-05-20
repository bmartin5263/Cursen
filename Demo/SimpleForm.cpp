//
// Created by Brandon Martin on 4/10/19.
//

#include "SimpleForm.h"

SimpleForm::SimpleForm() :
        Form(cursen::Vect2(70,33))
{

}

void SimpleForm::initialize() {

    modeSelectBox.initialize();
    modeSelectBox.setPosition(cursen::Vect2(17, 7));
    modeSelectBox.getMainPlayerStage().activateTextField();
}