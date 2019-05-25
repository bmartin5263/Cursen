//
// Created by Brandon Martin on 3/7/19.
//

#include "Cursen/CursenApplication.h"
#include "Cursen/Components/Component.h"
#include "Cursen/Drawing/CursesManager.h"
#include "Cursen/Events/EventType.h"
#include "AlarmManager.h"
#include "EventManager.h"

namespace cursen {

    EventManager *EventManager::instance = nullptr;

// Deprecated
    Event EventManager::privPollEvent() {
        while (eventQueue.isEmpty()) {
            AlarmManager::ProcessAlarms();
        }
        return eventQueue.pop();
    }

    void EventManager::processUpdates()
    {
        ComponentList& componentList = dispatchMap[EventType::Update];
        for (ComponentList::iterator listItem = componentList.begin(); listItem != componentList.end(); ++listItem) {
            std::function<bool()>& enableFunction = (*listItem)->GetEnableIf();
            std::function<void()>& updateFunction = (*listItem)->GetUpdate();
            if (enableFunction)
            {
                (*listItem)->setEnabled(enableFunction());
            }
            if (updateFunction)
            {
                updateFunction();
            }
        }
    }

    void EventManager::privProcessEvents() {
        processUpdates();
        while (!eventQueue.isEmpty()) {
            privProcessEvent(eventQueue.pop());
        }
    }

    void EventManager::privProcessEvent(const Event &event) {
        ComponentList componentList;
        switch (event.type) {
            case EventType::KeyPressed:
                componentList = dispatchMap[EventType::KeyPressed];
                for (ComponentList::iterator listItem = componentList.begin();
                     listItem != componentList.end(); ++listItem) {
                    (*listItem)->CallKeyPress(event);
                }
                break;
            case EventType::EscPressed:
                CursenApplication::Quit();
                break;
            case EventType::DeletePressed:
                componentList = dispatchMap[EventType::DeletePressed];
                for (ComponentList::iterator listItem = componentList.begin();
                     listItem != componentList.end(); ++listItem) {
                    (*listItem)->CallDeletePress(event);
                }
                break;
            case EventType::EnterPressed:
                componentList = dispatchMap[EventType::EnterPressed];
                for (ComponentList::iterator listItem = componentList.begin();
                     listItem != componentList.end(); ++listItem) {
                    (*listItem)->CallEnterPress(event);
                }
                break;
            case EventType::ArrowPressed:
                componentList = dispatchMap[EventType::ArrowPressed];
                for (ComponentList::iterator listItem = componentList.begin();
                     listItem != componentList.end(); ++listItem) {
                    (*listItem)->CallArrowPress(event);
                }
                break;
            case EventType::AlarmInterval:
                event.alarm.alarmEntry->callInterval();
                break;
            case EventType::AlarmExpire:
                event.alarm.alarmEntry->callExpire();
                break;
            case EventType::Update:
            case EventType::Null:
                break;
        }
    }

    void EventManager::deregisterComponent(Component &component, EventType eventFlag) {
        ComponentRegistrationMap::iterator it;

        it = registrationMap.find(&component);
        if (it != registrationMap.end()) {
            BitFlags currentFlags = it->second;

            for (BitFlags flag = (BitFlags) EventType::KeyPressed; flag < (BitFlags) EventType::Null; flag = flag << 1) {
                if (flag & currentFlags & (BitFlags) eventFlag) {
                    dispatchMap[(EventType) flag].erase(&component);
                    it->second -= flag;
                }
            }

            if (it->second == 0)
                registrationMap.erase(&component);
        }
    }

    void EventManager::registerComponent(Component &component, EventType eventFlag) {
        BitFlags currentFlags;

        auto it = registrationMap.find(&component);
        if (it != registrationMap.end()) {
            currentFlags = it->second;
        } else {
            registrationMap[&component] = 0;
            currentFlags = 0;
        }

        for (BitFlags flag = (BitFlags) EventType::KeyPressed; flag < (BitFlags) EventType::Null; flag = flag << 1) {
            if (flag & ~currentFlags & (BitFlags) eventFlag) {
                dispatchMap[(EventType) flag].insert(&component);
                registrationMap[&component] += flag;
            }
        }
    }

    SoloRegistrationKey *EventManager::registerComponentSolo(Component &component, EventType eventFlag) {
        return nullptr;
    }

    void EventManager::deregisterComponentSolo(SoloRegistrationKey *key, EventType events) {

    }

    EventQueue *EventManager::privGetEventQueue() {
        return &eventQueue;
    }

    void EventManager::privPushEvent(Event e) {
        eventQueue.push(e);
    }

    void EventManager::Terminate()
    {
        delete instance;
        instance = nullptr;
    }

}