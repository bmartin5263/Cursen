//
// Created by Brandon Martin on 7/27/19.
//

#include "VisualComponent.h"

namespace cursen
{

    void VisualComponent::setHidden(bool value)
    {
        hidden = value;
    }

    bool VisualComponent::isHidden() const
    {
        return hidden;
    }

    Vect2 VisualComponent::getPosition() const
    {
        return position;
    }

    void VisualComponent::setPosition(const Vect2& pos)
    {
        this->position = pos;
    }

    void VisualComponent::move(const Vect2& movement)
    {
        position += movement;
    }

    void VisualComponent::setCursable(bool value)
    {
        this->cursable = value;
    }

    bool VisualComponent::isCursable() const
    {
        return cursable;
    }

}