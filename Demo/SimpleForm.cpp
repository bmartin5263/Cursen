//
// Created by Brandon Martin on 4/10/19.
//

#include "SimpleForm.h"

SimpleForm::SimpleForm() :
        Form(Vect2(70,33))
{

}

void SimpleForm::initialize() {

    l1.initialize();
    l1.setPosition(Vect2(0,0));
    l1.setText("Label 1");
    l1.setDrawOrder(100);

    l2.initialize();
    l2.setPosition(Vect2(5,0));
    l2.setText("Label 2");
    l2.setDrawOrder(101);

    c.initialize();
    c.setPosition(Vect2(0,3));
    c.setText("fuck");
}