//
// Created by Brandon Martin on 2/21/19.
//

#include <functional>

#include "Form.h"
#include "Component.h"
#include "Cursen/Cursor/Cursor.h"

namespace cursen {

    Form::Form(const Vect2 &dim) :
            AggregateComponent(Vect2(0, 0)), dimensions(dim) {
        if (dim.x < 1 || dim.y < 1) throw std::logic_error("Form requires dimensions > 0");
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

        for (BitFlags flag = (BitFlags) EventType::KeyPressed; flag < (BitFlags) EventType::Null; flag = flag << 1) {
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

            for (BitFlags flag = (BitFlags) EventType::KeyPressed; flag < (BitFlags) EventType::Null; flag = flag << 1) {
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

    Form::EventComponentMap& Form::getDispatchMap()
    {
        return dispatchMap;
    }

    Form::ComponentRegistrationMap& Form::getEventRegistrationMap()
    {
        return eventRegistrationMap;
    }

    void Form::setDrawOrder(TextComponent* component, int order)
    {
        componentDrawMap[component->getDrawOrder()].erase(component);
        componentDrawMap[order].insert(component);
    }

}