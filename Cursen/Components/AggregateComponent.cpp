//
// Created by Brandon Martin on 4/3/19.
//

#include "AggregateComponent.h"

namespace cursen {

    AggregateComponent::AggregateComponent() {

    }

    AggregateComponent::AggregateComponent(const Vect2 &pos) :
            Component(pos) {

    }

    void AggregateComponent::setHidden(bool value) {
        Component::setHidden(value);
        for (auto child : getChildren()) {
            child->setHidden(value);
        }
    }

    void AggregateComponent::setEnabled(bool value) {
        Component::setEnabled(value);
        Component::setCursable(value);
        for (auto child : getChildren()) {
            child->setEnabled(value);
        }
    }

    void AggregateComponent::setPosition(const Vect2 &pos) {
        Vect2 difference = pos - getPosition();
        move(difference);
    }

    void AggregateComponent::setForeground(const Color &color) {
        Component::setForeground(color);
        for (auto child : getChildren()) {
            child->setForeground(color);
        }
    }

    void AggregateComponent::setDrawOrder(int order)
    {
        Component::setDrawOrder(order);
        for (auto child : getChildren()) {
            child->setDrawOrder(order);
        }
    }

}