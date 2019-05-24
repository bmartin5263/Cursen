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
        CursesManager::Register(this);
    }

    TextComponent::TextComponent(const Vect2 &pos) :
            Component(pos) {
        CursesManager::Register(this);
    }

    TextComponent::TextComponent(const Vect2 &pos, const Vect2 &dim) :
            Component(pos), content(dim) {
        CursesManager::Register(this);
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
        CursesManager::Deregister(this);
    }

    void TextComponent::setDrawOrder(int order)
    {
        CursesManager::SetDrawOrder(this, order);
        Component::setDrawOrder(order);
    }

}