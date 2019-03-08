//
// Created by Brandon Martin on 2/21/19.
//

#include <CursesManager.h>
#include <functional>
#include "Form.h"
#include "Component.h"

void Form::init() {
    Component* c = new Component;
    std::function<void(const Event&)> f = std::bind(&Form::keyPress, *this, std::placeholders::_1);
    std::function<void(const Event&)> f2 = std::bind(&Form::deletePress, *this, std::placeholders::_1);
    std::function<void(const Event&)> f3 = std::bind(&Form::enterPress, *this, std::placeholders::_1);
    std::function<void(const Event&)> f4 = std::bind(&Form::arrowPress, *this, std::placeholders::_1);
    c->onKeyPress(f);
    c->onDeletePress(f2);
    c->onEnterPress(f3);
    c->onArrowPress(f4);
}

void Form::keyPress(const Event& event) {
    CursesManager::PutCharacter(event.key.code);
}

void Form::deletePress(const Event &event) {
    CursesManager::PutCharacter('!');
}

void Form::enterPress(const Event &event) {
    CursesManager::PutCharacter('E');
}

void Form::arrowPress(const Event &event) {
    if (event.arrowPress.right) {
        CursesManager::PutCharacter('R');
    }
    if (event.arrowPress.left) {
        CursesManager::PutCharacter('L');
    }
    if (event.arrowPress.up) {
        CursesManager::PutCharacter('U');
    }
    if (event.arrowPress.down) {
        CursesManager::PutCharacter('D');
    }
}
