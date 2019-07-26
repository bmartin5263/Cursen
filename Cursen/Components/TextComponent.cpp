//
// Created by Brandon Martin on 4/3/19.
//

#include "Cursen/CursenApplication.h"
#include "Cursen/Events/AlarmManager.h"
#include "Cursen/Drawing/CursesManager.h"
#include "TextComponent.h"

namespace cursen {

    TextComponent::TextComponent() :
            Component(Vect2(0, 0)) {
    }

    TextComponent::TextComponent(const Vect2 &pos) :
            Component(pos) {
    }

    TextComponent::TextComponent(const Vect2 &pos, const Vect2 &dim) :
            Component(pos), content(dim) {
    }

    void TextComponent::initialize()
    {
        CursenApplication::Register(this);
    }

    void TextComponent::setSize(const Vect2 &size) {
        content.resize(size);
        invalidate();
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

    void TextComponent::setDrawOrder(const size_t order)
    {
        CursenApplication::SetDrawOrder(this, order);
        Component::setDrawOrder(order);
    }

    void TextComponent::addDrawOrder(int value)
    {
        CursenApplication::SetDrawOrder(this, Component::getDrawOrder() + value);
        Component::addDrawOrder(value);
    }

}