//
// Created by Brandon Martin on 2/21/19.
//

#include <Drawing/CursesManager.h>
#include <functional>
#include "Form.h"
#include "Component.h"
#include "Cursor.h"

void Form::Initialize() {
    c = new Component;
    Cursor* cursor = new Cursor(c);

    cursor->setEnabled(true);
    cursor->addComponent(c, ArrowMap(c,c,c,c));

    c->onClick(std::bind(&Form::clickComponent, this));
    c->onArrowPress(std::bind(&Form::arrowPress, this, std::placeholders::_1));
}

void Form::clickComponent() {
    c->move(Vect2d(0,1));
    c->refresh();
}

void Form::arrowPress(const Event& e) {
    if (e.arrowPress.left) {
        c->move(Vect2d(-1,0));
    }
    if (e.arrowPress.right) {
        c->move(Vect2d(1,0));
    }
    if (e.arrowPress.down) {
        c->move(Vect2d(0,1));
    }
    if (e.arrowPress.up) {
        c->move(Vect2d(0,-1));
    }
}


