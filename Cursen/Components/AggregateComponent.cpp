//
// Created by Brandon Martin on 4/3/19.
//

#include <cassert>
#include "AggregateComponent.h"

namespace cursen {

    AggregateComponent::AggregateComponent() :
        min_order(0), max_order(0)
    {
    }

    AggregateComponent::AggregateComponent(const Vect2 &pos) :
            VisualComponent(pos), min_order(0), max_order(0)
    {
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
        if (order != getDrawOrder())
        {
            size_t diff = order - min_order;
            for (auto child : children) {
                child->addDrawOrder(diff);
            }
            this->max_order += diff;
            this->min_order += diff;
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
        children.push_back(&component);

        size_t order = component.getDrawOrder();

        if (order > getMaxOrder())
        {
            max_order = order;
        }
        if (order < getMinOrder())
        {
            min_order = order;
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
        return getMaxOrder();
    }

    size_t AggregateComponent::getMinOrder() const
    {
        return min_order;
    }

    size_t AggregateComponent::getMaxOrder() const
    {
        return max_order;
    }

}