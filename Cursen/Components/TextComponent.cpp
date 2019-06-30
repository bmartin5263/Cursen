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

    Vect2 TextComponent::getSize() {
        return content.getDimensions();
    }

    Content& TextComponent::getContent() {
        return content;
    }

    TextComponent::~TextComponent()
    {
        CursenApplication::Deregister(this);
    }

    void TextComponent::setDrawOrder(int order)
    {
        CursenApplication::SetDrawOrder(this, order);
        Component::setDrawOrder(order);
    }

}