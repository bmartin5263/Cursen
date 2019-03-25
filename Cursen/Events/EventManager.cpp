//
// Created by Brandon Martin on 3/7/19.
//

#include <CursenApplication.h>
#include <Components/Component.h>
#include "EventManager.h"
#include "Drawing/CursesManager.h"
#include "Events/EventType.h"

EventManager* EventManager::instance = nullptr;

void EventManager::processKeyboardInput(int limit) {
    int keysProcessed = 0;
    int key = getch();
    while(key != ERR) {
        Event event;
        if (key == CursesManager::ESCAPE) {
            event.type = EventType::EscPressed;
            event.key.code = key;
        }
        else if (key == CursesManager::BACKSPACE)
        {
            event.type = EventType::DeletePressed;
            event.key.code = key;
        }
        else if (key == CursesManager::ENTER)
        {
            event.type = EventType::EnterPressed;
            event.key.code = key;
        }
        else if (key == CursesManager::UP)
        {
            event.type = EventType::ArrowPressed;
            event.arrowPress.up = true;
        }
        else if (key == CursesManager::DOWN)
        {
            event.type = EventType::ArrowPressed;
            event.arrowPress.down = true;
        }
        else if (key == CursesManager::LEFT)
        {
            event.type = EventType::ArrowPressed;
            event.arrowPress.left = true;

        }
        else if (key == CursesManager::RIGHT)
        {
            event.type = EventType::ArrowPressed;
            event.arrowPress.right = true;
        }
        else
        {
            event.type = EventType::KeyPressed;
            event.key.code = key;
        }
        eventQueue.push(event);
        keysProcessed++;
        if (keysProcessed == limit) {
            return;
        }
        key = getch();
    }
}

Event EventManager::pollEvent() {
    Event event;
    while (eventQueue.isEmpty()) {
        processKeyboardInput(10);
    }
    eventQueue.pop(event);
    return event;
}

void EventManager::processEvent(const Event &event) {
    ComponentList componentList;
    switch (event.type) {
        case EventType::KeyPressed:
            componentList = dispatchMap[EventType::KeyPressed];
            for (ComponentList::iterator listItem = componentList.begin(); listItem != componentList.end(); ++listItem) {
                (*listItem)->CallKeyPress(event);
            }
            break;
        case EventType::EscPressed:
            CursenApplication::Quit();
            break;
        case EventType::DeletePressed:
            componentList = dispatchMap[EventType::DeletePressed];
            for (ComponentList::iterator listItem = componentList.begin(); listItem != componentList.end(); ++listItem) {
                (*listItem)->CallDeletePress(event);
            }
            break;
        case EventType::EnterPressed:
            componentList = dispatchMap[EventType::EnterPressed];
            for (ComponentList::iterator listItem = componentList.begin(); listItem != componentList.end(); ++listItem) {
                (*listItem)->CallEnterPress(event);
            }
            break;
        case EventType::SocketConnected:
            componentList = dispatchMap[EventType::SocketConnected];
            for (ComponentList::iterator listItem = componentList.begin(); listItem != componentList.end(); ++listItem) {
                (*listItem)->CallSocketConnect(event);
            }
            break;
        case EventType::SocketDisconnected:
            componentList = dispatchMap[EventType::SocketDisconnected];
            for (ComponentList::iterator listItem = componentList.begin(); listItem != componentList.end(); ++listItem) {
                (*listItem)->CallSocketDisconnect(event);
            }
            break;
        case EventType::SocketMessage:
            componentList = dispatchMap[EventType::SocketMessage];
            for (ComponentList::iterator listItem = componentList.begin(); listItem != componentList.end(); ++listItem) {
                (*listItem)->CallSocketMessage(event);
            }
            break;
        case EventType::ArrowPressed:
            componentList = dispatchMap[EventType::ArrowPressed];
            for (ComponentList::iterator listItem = componentList.begin(); listItem != componentList.end(); ++listItem) {
                (*listItem)->CallArrowPress(event);
            }
            break;
    }
}

void EventManager::deregisterComponent(Component &component, EventType eventFlag) {
    ComponentFlagMap::iterator it;

    it = registrationMap.find(&component);
    if (it != registrationMap.end() )
    {
        BitFlags currentflags = it->second;

        for (BitFlags flag = (BitFlags)EventType::KeyPressed; flag <= (BitFlags)EventType::SocketMessage; flag = flag << 1)
        {
            if (flag & currentflags & (BitFlags)eventFlag)
            {
                dispatchMap[(EventType)flag].erase(&component);
                it->second -= flag;
            }
        }

        if (it->second == 0)
            registrationMap.erase(&component);
    }
}

void EventManager::registerComponent(Component& component, EventType eventFlag) {
    ComponentFlagMap::iterator it;
    BitFlags currentFlags;

    it = registrationMap.find(&component);
    if (it != registrationMap.end())
    {
        currentFlags = it->second;
    }
    else
    {
        registrationMap[&component] = 0;
        currentFlags = 0;
    }

    for( BitFlags flag = (BitFlags)EventType::KeyPressed; flag <= (BitFlags)EventType::SocketMessage; flag = flag << 1 )
    {
        if (flag & ~currentFlags & (BitFlags)eventFlag)
        {
            dispatchMap[(EventType)flag].insert(&component);
            registrationMap[&component] += flag;
        }
    }
}

EventQueue* EventManager::privGetEventQueue() {
    return &eventQueue;
}