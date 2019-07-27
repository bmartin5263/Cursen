//
// Created by Brandon Martin on 4/3/19.
//

#include <cassert>
#include "AggregateComponent.h"

namespace cursen {

    AggregateComponent::AggregateComponent() {

    }

    AggregateComponent::AggregateComponent(const Vect2 &pos) :
            VisualComponent(pos) {

    }

    void AggregateComponent::setHidden(bool value) {
        VisualComponent::setHidden(value);
        for (auto child : children) {
            child->setHidden(value);
        }
    }

    void AggregateComponent::setEnabled(bool value) {
        Component::setEnabled(value);
        VisualComponent::setCursable(value);
        for (auto child : children) {
            child->setEnabled(value);
        }
    }

    void AggregateComponent::setPosition(const Vect2 &pos) {
        Vect2 difference = pos - getPosition();
        move(difference);
    }

    void AggregateComponent::setForeground(const Color &color) {
        VisualComponent::setForeground(color);
        for (auto child : children) {
            child->setForeground(color);
        }
    }

    void AggregateComponent::setDrawOrder(size_t order)
    {
        size_t curr = getDrawOrder();
        if (curr != order)
        {
            size_t diff = order - curr;
            this->order += diff;
            for (auto child : children) {
                child->addDrawOrder(diff);
            }
        }
    }

    void AggregateComponent::setHighlight(const ColorPair& colorPair)
    {
        VisualComponent::setHighlight(colorPair);
        for (auto child : children) {
            child->setHighlight(colorPair);
        }
    }

    void AggregateComponent::move(const Vect2& movement)
    {
        VisualComponent::move(movement);
        for (auto child : children) {
            child->move(movement);
        }
    }

    void AggregateComponent::setSilenced(bool value)
    {
        Component::setSilenced(value);
        for (auto child : children) {
            child->setSilenced(value);
        }
    }

    void AggregateComponent::setCursable(bool value)
    {
        VisualComponent::setCursable(value);
        for (auto child : children) {
            child->setCursable(value);
        }
    }

    void AggregateComponent::setBackground(const Color& color)
    {
        VisualComponent::setBackground(color);
        for (auto child : children) {
            child->setBackground(color);
        }
    }

    void AggregateComponent::setDisabled(const ColorPair& color)
    {
        VisualComponent::setDisabled(color);
        for (auto child : children) {
            child->setDisabled(color);
        }
    }

    void AggregateComponent::setText(const std::string& text)
    {
        VisualComponent::setText(text);
        for (auto child : children) {
            child->setText(text);
        }
    }

    void AggregateComponent::add(VisualComponent& component)
    {
        component.setParent(this);
        //component->setDrawOrder(component->getDrawOrder() + this->drawOrder + 1);
        children.push_back(&component);
        if (component.getDrawOrder() > getDrawOrder())
        {
           order = component.getDrawOrder();
        }
    }

    void AggregateComponent::addRelative(VisualComponent& component)
    {
        component.move(getPosition());
        add(component);
    }

    void AggregateComponent::drawOnTopOf(VisualComponent& component)
    {
        size_t order = component.getDrawOrder();
        setDrawOrder(order + 1);
    }

    void AggregateComponent::addDrawOrder(const size_t value)
    {
        setDrawOrder(getDrawOrder() + value);
    }

    size_t AggregateComponent::getDrawOrder() const
    {
        return order;
    }

}