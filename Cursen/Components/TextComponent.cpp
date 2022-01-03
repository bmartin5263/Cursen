//
// Created by Brandon Martin on 4/3/19.
//

#include "Cursen/CursenApplication.h"
#include "Cursen/Events/AlarmManager.h"
#include "Cursen/Drawing/TerminalManager.h"
#include "TextComponent.h"

namespace cursen {

    TextComponent::TextComponent() :
            VisualComponent(Vect2(0, 0)), order(0), invalid(true)
    {
    }

    TextComponent::TextComponent(const Vect2 &pos) :
            VisualComponent(pos), order(0), invalid(true)
    {
    }

    TextComponent::TextComponent(const Vect2 &pos, const Vect2 &dim) :
            VisualComponent(pos), content(dim), order(0), invalid(true)
    {
    }

    void TextComponent::initialize()
    {
        CursenApplication::Register(this);
    }

    void TextComponent::setSize(const Vect2 &size) {
        if (size != content.getSize())
        {
            content.resize(size);
            invalidate();
        }
    }

    Vect2 TextComponent::getSize() const {
        return content.getSize();
    }

    Content& TextComponent::getContent() {
        return content;
    }

    const Content& TextComponent::getContentConst() const
    {
        return content;
    }

    TextComponent::~TextComponent()
    {
        CursenApplication::Deregister(this);
    }

    size_t TextComponent::getDrawOrder() const
    {
        return order;
    }

    void TextComponent::setDrawOrder(size_t order)
    {
        CursenApplication::SetDrawOrder(this, order);
        this->order = order;
    }

    void TextComponent::addDrawOrder(size_t value)
    {
        setDrawOrder(order + value);
    }

    void TextComponent::drawOnTopOf(VisualComponent& component)
    {
        setDrawOrder(component.getDrawOrder() + 1);
    }

    void TextComponent::invalidate()
    {
        invalid = true;
    }

    void TextComponent::validate()
    {
        invalid = false;
    }

    bool TextComponent::isInvalid() const
    {
        return invalid;
    }

    void TextComponent::setPosition(const Vect2& pos)
    {
        VisualComponent::setPosition(pos);
        invalidate();
    }

    void TextComponent::move(const Vect2& movement)
    {
        VisualComponent::move(movement);
        invalidate();
    }

}