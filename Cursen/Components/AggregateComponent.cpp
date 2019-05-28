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
        Component::move(difference);
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

    void AggregateComponent::setHighlight(const ColorPair& colorPair)
    {
        Component::setHighlight(colorPair);
        for (auto child : getChildren()) {
            child->setHighlight(colorPair);
        }
    }

    void AggregateComponent::move(const Vect2& movement)
    {
        Component::move(movement);
        //for (auto child : getChildren()) {
        //    child->move(movement);
        //}
    }

    void AggregateComponent::setSilenced(bool value)
    {
        Component::setSilenced(value);
        for (auto child : getChildren()) {
            child->setSilenced(value);
        }
    }

    void AggregateComponent::setCursable(bool value)
    {
        Component::setCursable(value);
        for (auto child : getChildren()) {
            child->setCursable(value);
        }
    }

    void AggregateComponent::setBackground(const Color& color)
    {
        Component::setBackground(color);
        for (auto child : getChildren()) {
            child->setBackground(color);
        }
    }

    void AggregateComponent::setDisabled(const ColorPair& color)
    {
        Component::setDisabled(color);
        for (auto child : getChildren()) {
            child->setDisabled(color);
        }
    }

    void AggregateComponent::setText(const std::string& text)
    {
        Component::setText(text);
        for (auto child : getChildren()) {
            child->setText(text);
        }
    }

}