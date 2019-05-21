//
// Created by Brandon Martin on 4/10/19.
//

#include "SimpleForm.h"

SimpleForm::SimpleForm() :
        Form(cursen::Vect2(70,33))
{

}

void SimpleForm::initialize()
{
    myBox.initialize();
    myBox.setSize(cursen::Vect2(30,3));
    myBox.setPosition(cursen::Vect2(1,1));
    myBox.setForeground(cursen::Color::VIOLET);
    myBox.setFill(cursen::Content::INVISIBLE);
    myBox.setDrawOrder(100);

    myLabel.initialize();
    myLabel.setPosition(cursen::Vect2(2,2));
    myLabel.setText("Hello World!");
    myLabel.setForeground(cursen::Color::YELLOW);
    myLabel.setDrawOrder(1);
}