//
// Created by Brandon Martin on 3/7/19.
//

#include "Cursen/CursenApplication.h"
#include "Cursen/Components/Component.h"
#include "Cursen/Drawing/TerminalManager.h"
#include "Cursen/Events/EventType.h"
#include "AlarmManager.h"
#include "EventManager.h"

namespace cursen {

    void EventManager::processUpdates(EventManager::EventComponentMap& dispatchMap)
    {
        ComponentList& componentList = dispatchMap[EventType::Update];
        auto cend = componentList.cend();
        for (ComponentList::const_iterator listItem = componentList.cbegin(); listItem != cend; ++listItem) {
            Component* component = (*listItem);
            const std::function<bool()>& enableFunction = component->GetEnableIf();
            const std::function<void()>& updateFunction = component->GetUpdate();
            if (enableFunction)
            {
                bool enabled = enableFunction();
                if (component->isEnabled() != enabled) component->setEnabled(enabled);
            }
            if (updateFunction)
            {
                updateFunction();
            }
        }
    }

    void EventManager::ProcessEvents(EventManager::EventComponentMap& dispatchMap)
    {
        auto& instance = Instance();
        instance.processUpdates(dispatchMap);
        while (!instance.eventQueue.isEmpty()) {
            instance.privProcessEvent(dispatchMap, instance.eventQueue.pop());
        }
    }

    void EventManager::privProcessEvent(EventManager::EventComponentMap& dispatchMap, const Event& event)
    {
        ComponentList componentList;
        switch (event.type) {
            case EventType::KeyPressed:
                componentList = dispatchMap[EventType::KeyPressed];
                for (auto listItem = componentList.cbegin(); listItem != componentList.cend(); ++listItem) {
                    (*listItem)->CallKeyPress(event);
                }
                break;
            case EventType::EscPressed:
                componentList = dispatchMap[EventType::EscPressed];
                for (auto listItem = componentList.cbegin(); listItem != componentList.cend(); ++listItem) {
                    (*listItem)->CallEscapePress(event);
                }
                break;
            case EventType::DeletePressed:
                componentList = dispatchMap[EventType::DeletePressed];
                for (auto listItem = componentList.cbegin(); listItem != componentList.cend(); ++listItem) {
                    (*listItem)->CallDeletePress(event);
                }
                break;
            case EventType::EnterPressed:
                componentList = dispatchMap[EventType::EnterPressed];
                for (auto listItem = componentList.cbegin(); listItem != componentList.cend(); ++listItem) {
                    (*listItem)->CallEnterPress(event);
                }
                break;
            case EventType::ArrowPressed:
                componentList = dispatchMap[EventType::ArrowPressed];
                for (auto listItem = componentList.cbegin(); listItem != componentList.cend(); ++listItem) {
                    (*listItem)->CallArrowPress(event);
                }
                break;
            case EventType::AnyKeyPressed:
                componentList = dispatchMap[EventType::AnyKeyPressed];
                for (auto listItem = componentList.cbegin(); listItem != componentList.cend(); ++listItem) {
                    (*listItem)->CallAnyKeyPress(event);
                }
                break;
            case EventType::KeyDown:
                componentList = dispatchMap[EventType::KeyDown];
                for (auto listItem = componentList.cbegin(); listItem != componentList.cend(); ++listItem) {
                    (*listItem)->CallKeyDown(event);
                }
                break;
            case EventType::KeyUp:
                componentList = dispatchMap[EventType::KeyUp];
                for (auto listItem = componentList.cbegin(); listItem != componentList.cend(); ++listItem) {
                    (*listItem)->CallKeyUp(event);
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
        CursenApplication::GetCurrentForm()->deregisterForEvents(&component, eventFlag);
    }

    void EventManager::registerComponent(Component &component, EventType eventFlag) {
        CursenApplication::GetCurrentForm()->registerForEvents(&component, eventFlag);
    }

    EventManager& EventManager::Instance()
    {
        return CursenApplication::GetEventManager();
    }

    void EventManager::processEvents(EventManager::EventComponentMap& dispatchMap)
    {
        processUpdates(dispatchMap);
        while (!eventQueue.isEmpty())
        {
            privProcessEvent(dispatchMap, eventQueue.pop());
        }
    }


}