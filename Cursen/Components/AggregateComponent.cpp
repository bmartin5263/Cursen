//
// Created by Brandon Martin on 4/3/19.
//

#include "AggregateComponent.h"

AggregateComponent::AggregateComponent()
{

}

AggregateComponent::AggregateComponent(const Size &pos) :
    Component(pos)
{

}

void AggregateComponent::setHidden(bool value) {
    Component::setHidden(value);
    for (auto child : getChildren()) {
        child->setHidden(value);
    }
}

void AggregateComponent::setEnabled(bool value) {
    Component::setEnabled(value);
    for (auto child : getChildren()) {
        child->setEnabled(value);
    }
}

void AggregateComponent::setPosition(const Size &pos) {
    Size difference = pos - getPosition();
    move(difference);
}

void AggregateComponent::setForeground(const Color &color) {
    Component::setForeground(color);
    for (auto child : getChildren()) {
        child->setForeground(color);
    }
}
