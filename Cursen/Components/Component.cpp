//
// Created by Brandon Martin on 3/8/19.
//

#include <cassert>
#include <algorithm>

#include "Cursen/CursenApplication.h"
#include "Cursen/Drawing/CursesManager.h"
#include "Cursen/Events/EventManager.h"
#include "Component.h"

namespace cursen
{

    Component::Component() :
            id("n/a"), f_keyPress(), f_escapePress(), f_enterPress(), f_deletePress(), f_arrowPress(), f_update(),
            f_onCursor(), f_offCursor(), f_onClick(), f_enableIf(), parent(nullptr), children(), position(),
            drawOrder(0), enabled(true), invalid(true), hidden(false), silenced(false), cursable(true),
            registeredForUpdates(false)
    {
        id = "n/a";
    }

    Component::Component(const Vect2& pos) :
            id("n/a"), f_keyPress(), f_escapePress(), f_enterPress(), f_deletePress(), f_arrowPress(), f_update(),
            f_onCursor(), f_offCursor(), f_onClick(), f_enableIf(), parent(nullptr), children(), position(pos),
            drawOrder(0), enabled(true), invalid(true), hidden(false), silenced(false), cursable(true),
            registeredForUpdates(false)
    {
        id = "n/a";
    }

    void Component::add(Component* component)
    {
        assert(component != nullptr);
        component->setParent(this);
        //component->setDrawOrder(component->getDrawOrder() + this->drawOrder + 1);
        children.push_back(component);
    }

    void Component::addRelative(Component* component)
    {
        assert(component != nullptr);
        component->move(this->position);
        add(component);
    }

    void Component::remove(Component* component)
    {
        component->setParent(nullptr);
        children.erase(std::remove(children.begin(), children.end(), component), children.end());
    }

    Component* Component::getParent()
    {
        return parent;
    }

    void Component::setParent(Component* component)
    {
        this->parent = component;
    }

    void Component::onKeyPress(std::function<void(const Event&)> f)
    {
        EventManager::Register(*this, EventType::KeyPressed);
        f_keyPress = f;
    }

    void Component::onEscapePress(std::function<void(const Event&)> f)
    {
        EventManager::Register(*this, EventType::EscPressed);
        f_escapePress = f;
    }

    void Component::onEnterPress(std::function<void(const Event&)> f)
    {
        EventManager::Register(*this, EventType::EnterPressed);
        f_enterPress = f;
    }

    void Component::onDeletePress(std::function<void(const Event&)> f)
    {
        EventManager::Register(*this, EventType::DeletePressed);
        f_deletePress = f;
    }

    void Component::onArrowPress(std::function<void(const Event&)> f)
    {
        EventManager::Register(*this, EventType::ArrowPressed);
        f_arrowPress = f;
    }

    void Component::enableIf(std::function<bool()> f)
    {
        if (!registeredForUpdates)
        {
            EventManager::Register(*this, EventType::Update);
            registeredForUpdates = true;
        }
        f_enableIf = f;
    }

    void Component::onCursor(std::function<void()> f)
    {
        f_onCursor = f;
    }

    void Component::offCursor(std::function<void()> f)
    {
        f_offCursor = f;
    }

    void Component::onClick(std::function<void()> f)
    {
        f_onClick = f;
    }

    void Component::onUpdate(std::function<void()> f)
    {
        if (!registeredForUpdates)
        {
            EventManager::Register(*this, EventType::Update);
            registeredForUpdates = true;
        }
        f_update = f;
    }

    void Component::setEnabled(bool value)
    {
        this->enabled = value;
    }

    bool Component::isEnabled() const
    {
        return enabled;
    }

    void Component::setHidden(bool value)
    {
        hidden = value;
    }

    bool Component::isHidden() const
    {
        return hidden;
    }

    void Component::CallKeyPress(const Event& e) const
    {
        if (!isSilenced())
        {
            if (f_keyPress) f_keyPress(e);;
        }
    }

    void Component::CallEscapePress(const Event& e) const
    {
        if (!isSilenced())
        {
            if (f_escapePress) f_escapePress(e);
        }
    }

    void Component::CallEnterPress(const Event& e) const
    {
        if (!isSilenced())
        {
            if (f_enterPress) f_enterPress(e);
        }
    }

    void Component::CallDeletePress(const Event& e) const
    {
        if (!isSilenced())
        {
            if (f_deletePress) f_deletePress(e);
        }
    }

    void Component::CallArrowPress(const Event& e) const
    {
        if (!isSilenced())
        {
            if (f_arrowPress) f_arrowPress(e);
        }
    }

    void Component::CallOnCursor() const
    {
        if (f_onCursor) f_onCursor();
    }

    void Component::CallOffCursor() const
    {
        if (f_offCursor) f_offCursor();
    }

    void Component::CallOnClick() const
    {
        if (f_onClick) f_onClick();
    }

    const std::function<bool()>& Component::GetEnableIf() const
    {
        return f_enableIf;
    }

    const std::function<void()>& Component::GetUpdate() const
    {
        return f_update;
    }

    void Component::detachKeyPress()
    {
        EventManager::Deregister(*this, EventType::KeyPressed);
        f_keyPress = 0;
    }

    void Component::detachEscapePress()
    {
        EventManager::Deregister(*this, EventType::EscPressed);
        f_escapePress = 0;
    }

    void Component::detachEnterPress()
    {
        EventManager::Deregister(*this, EventType::EnterPressed);
        f_enterPress = 0;
    }

    void Component::detachDeletePress()
    {
        EventManager::Deregister(*this, EventType::DeletePressed);
        f_deletePress = 0;
    }

    void Component::detachArrowPress()
    {
        EventManager::Deregister(*this, EventType::ArrowPressed);
        f_arrowPress = 0;
    }

    void Component::detachOnCursor()
    {
        f_onCursor = 0;
    }

    void Component::detachOnClick()
    {
        f_onClick = 0;
    }

    void Component::detachOffCursor()
    {
        f_offCursor = 0;
    }

    void Component::detachEnableIf()
    {
        f_enableIf = 0;
    }

    void Component::detachUpdate()
    {
        f_update = 0;
    }

    void Component::move(const Vect2& movement)
    {
        position += movement;
        for (auto child : children)
        {
            child->move(movement);
        }
    }

    void Component::invalidate()
    {
        invalid = true;
    }

    void Component::validate()
    {
        invalid = false;
    }

    bool Component::isInvalid() const
    {
        return invalid;
    }

    Vect2 Component::getPosition() const
    {
        return this->position;
    }

    void Component::setPosition(const Vect2& pos)
    {
        this->position = pos;
        invalidate();
    }

    const std::vector<Component*>& Component::getChildren()
    {
        return children;
    }

    Component::~Component()
    {
    }

    size_t Component::getDrawOrder() const
    {
        return drawOrder;
    }

    void Component::setDrawOrder(const size_t order)
    {
        drawOrder = order;
    }

    void Component::setSilenced(bool value)
    {
        this->silenced = value;
    }

    bool Component::isSilenced() const
    {
        return silenced;
    }

    void Component::setCursable(bool value)
    {
        this->cursable = value;
    }

    bool Component::isCursable() const
    {
        return cursable;
    }

    void Component::drawOnTopOf(const Component& component)
    {
        Component::setDrawOrder(component.getDrawOrder() + 1);
    }

    void Component::addDrawOrder(const int value)
    {
        Component::setDrawOrder(Component::getDrawOrder() + value);
    }


}