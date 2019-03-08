//
// Created by Brandon Martin on 3/8/19.
//

#include "Events/EventManager.h"
#include "Component.h"

void Component::ForKeyPress(std::function<void(const Event&)> fun) {
    EventManager::Register(*this, Event::KeyPressed);
    onKeyPress = fun;
}
