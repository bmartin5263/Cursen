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
    c->onKeyPress(f);
    c->onDeletePress(f2);
    c->onEnterPress(f3);
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
