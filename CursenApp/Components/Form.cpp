//
// Created by Brandon Martin on 2/21/19.
//

#include <CursesManager.h>
#include <functional>
#include "Form.h"
#include "Component.h"

void Form::init() {
    Component* c = new Component;
    std::function<void(const Event&)> f = std::bind(&Form::buttonClick, *this, std::placeholders::_1);
    c->ForKeyPress(f);
}

void Form::buttonClick(const Event& event) {
    CursesManager::PutCharacter(event.key.code);
}
