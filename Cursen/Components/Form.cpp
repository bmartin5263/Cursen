//
// Created by Brandon Martin on 2/21/19.
//

#include <functional>
#include <cassert>

#include "Form.h"
#include "Component.h"
#include "Cursen/Cursor/Cursor.h"
#include "Cursen/CursenApplication.h"

namespace cursen {

    Form::Form(const Vect2 &dim) :
            AggregateComponent(Vect2(0, 0)), dimensions(dim) {
        assert(dim.x > 0);
        assert(dim.y > 0);
    }

    Vect2 Form::getSize() {
        return dimensions;
    }

    void Form::registerComponent(TextComponent* component)
    {
        auto it = componentDrawMap[component->getDrawOrder()].find(component);
        if (it == componentDrawMap[component->getDrawOrder()].end())
        {
            componentDrawMap[component->getDrawOrder()].insert(component);
        }
    }

    void Form::deregisterComponent(TextComponent* component)
    {
        auto it = componentDrawMap[component->getDrawOrder()].find(component);
        if (it != componentDrawMap[component->getDrawOrder()].end())
        {
            componentDrawMap[component->getDrawOrder()].erase(component);
        }
    }

    std::map<int, std::set<TextComponent*>>& Form::getComponentDrawMap()
    {
        return componentDrawMap;
    }

    Form::CursorSet& Form::getCursors()
    {
        return cursors;
    }

    void Form::registerForEvents(Component* component, EventType events)
    {
        BitFlags currentFlags;

        auto it = eventRegistrationMap.find(component);
        if (it != eventRegistrationMap.end()) {
            currentFlags = it->second;
        } else {
            eventRegistrationMap[component] = 0;
            currentFlags = 0;
        }

        for (BitFlags flag = (BitFlags) EventType::KeyPressed; flag <= (BitFlags) EventType::KeyUp; flag = flag << 1) {
            if (flag & ~currentFlags & (BitFlags) events) {
                dispatchMap[(EventType) flag].insert(component);
                eventRegistrationMap[component] += flag;
            }
        }
    }

    void Form::deregisterForEvents(Component* component, EventType events)
    {
        ComponentRegistrationMap::iterator it;

        it = eventRegistrationMap.find(component);
        if (it != eventRegistrationMap.end()) {
            BitFlags currentFlags = it->second;

            for (BitFlags flag = (BitFlags) EventType::KeyPressed; flag <= (BitFlags) EventType::KeyUp; flag = flag << 1) {
                if (flag & currentFlags & (BitFlags) events) {
                    dispatchMap[(EventType) flag].erase(component);
                    it->second -= flag;
                }
            }

            if (it->second == 0)
                eventRegistrationMap.erase(component);
        }
    }

    void Form::registerCursor(Cursor* cursor)
    {
        if (cursors.find(cursor) == cursors.end()) {
            cursors.insert(cursor);
        }
    }

    void Form::deregisterCursor(Cursor* cursor)
    {
        if (cursors.find(cursor) != cursors.end()) {
            cursors.erase(cursor);
        }
    }

    Form::AlarmMap& Form::getAlarmMap()
    {
        return alarmMap;
    }

    Form::EventComponentMap& Form::getEventDispatchMap()
    {
        return dispatchMap;
    }

    Form::ComponentRegistrationMap& Form::getEventRegistrationMap()
    {
        return eventRegistrationMap;
    }

    void Form::setComponentDrawOrder(TextComponent* component, size_t order)
    {
        size_t currentDrawOrder = component->getDrawOrder();
        auto it = componentDrawMap[currentDrawOrder].find(component);
        if (it != componentDrawMap[currentDrawOrder].end())
        {
            componentDrawMap[currentDrawOrder].erase(component);
            componentDrawMap[order].insert(component);
        }
    }

    Form::AlarmQueue& Form::getStartRequests()
    {
        return startRequests;
    }

    Form::IntQueue& Form::getStopRequests()
    {
        return stopRequests;
    }

    void Form::onOpen(Form::VoidFunction f)
    {
        fOpen = f;
    }

    void Form::onClosed(Form::CloseFunction f)
    {
        fClose = f;
    }

    void Form::detachOnOpen()
    {
        fOpen = 0;
    }

    void Form::detachOnClosed()
    {
        fClose = 0;
    }

    void Form::CallOnOpen()
    {
        if (fOpen) fOpen();
    }

    void Form::CallOnClosed(void* return_value)
    {
        if (fClose) fClose(return_value);
    }

    void Form::closeForm(void* return_value)
    {
        cursen::CursenApplication::CloseForm(return_value);
    }

    void Form::openForm(Form* form)
    {
        cursen::CursenApplication::OpenForm(form);
    }

    void Form::beforeClosing(Form::VoidFunction f)
    {
        fBeforeClose = f;
    }

    void Form::detachBeforeClosing()
    {
        fBeforeClose = 0;
    }

    void Form::CallBeforeClosing()
    {
        if (fBeforeClose) fBeforeClose();
    }

}