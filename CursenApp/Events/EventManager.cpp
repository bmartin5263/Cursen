//
// Created by Brandon Martin on 3/7/19.
//

#include <CursenApplication.h>
#include <Components/Component.h>
#include "EventManager.h"
#include "CursesManager.h"

EventManager* EventManager::instance = nullptr;

Event EventManager::pollEvent() {
    Event event;

    int key = CursesManager::GetCharacter();

    if (key == CursesManager::ESCAPE) {
        event.type = Event::EscPressed;
        event.key.code = key;
    }
    else if (key == CursesManager::BACKSPACE)
    {
        event.type = Event::DeletePressed;
        event.key.code = key;
    }
    else if (key == CursesManager::ENTER)
    {
        event.type = Event::EnterPressed;
        event.key.code = key;
    }
    else if (key == CursesManager::UP)
    {
        event.type = Event::ArrowPressed;
        event.arrowPress.up = true;
    }
    else if (key == CursesManager::DOWN)
    {
        event.type = Event::ArrowPressed;
        event.arrowPress.down = true;
    }
    else if (key == CursesManager::LEFT)
    {
        event.type = Event::ArrowPressed;
        event.arrowPress.left = true;

    }
    else if (key == CursesManager::RIGHT)
    {
        event.type = Event::ArrowPressed;
        event.arrowPress.right = true;
    }
    else
    {
        event.type = Event::KeyPressed;
        event.key.code = key;
    }

    return event;
}

void EventManager::processEvent(Event &event) {
    ComponentList componentList;
    switch (event.type) {
        case Event::KeyPressed:
            componentList = dispatchMap[Event::KeyPressed];
            for (ComponentList::iterator listItem = componentList.begin(); listItem != componentList.end(); ++listItem) {
                (*listItem)->f_keyPress(event);
            }
            break;
        case Event::EscPressed:
            CursenApplication::Quit();
            break;
        case Event::DeletePressed:
            componentList = dispatchMap[Event::DeletePressed];
            for (ComponentList::iterator listItem = componentList.begin(); listItem != componentList.end(); ++listItem) {
                (*listItem)->f_deletePress(event);
            }
            break;
        case Event::EnterPressed:
            componentList = dispatchMap[Event::EnterPressed];
            for (ComponentList::iterator listItem = componentList.begin(); listItem != componentList.end(); ++listItem) {
                (*listItem)->f_enterPress(event);
            }
            break;
        case Event::SocketConnected:
            componentList = dispatchMap[Event::SocketConnected];
            for (ComponentList::iterator listItem = componentList.begin(); listItem != componentList.end(); ++listItem) {
                (*listItem)->f_socketConnect(event);
            }
            break;
        case Event::SocketDisconnected:
            componentList = dispatchMap[Event::SocketDisconnected];
            for (ComponentList::iterator listItem = componentList.begin(); listItem != componentList.end(); ++listItem) {
                (*listItem)->f_socketDisconnect(event);
            }
            break;
        case Event::SocketMessage:
            componentList = dispatchMap[Event::SocketMessage];
            for (ComponentList::iterator listItem = componentList.begin(); listItem != componentList.end(); ++listItem) {
                (*listItem)->f_socketMessage(event);
            }
            break;
        case Event::ArrowPressed:
            componentList = dispatchMap[Event::ArrowPressed];
            for (ComponentList::iterator listItem = componentList.begin(); listItem != componentList.end(); ++listItem) {
                (*listItem)->f_arrowPress(event);
            }
            break;
    }
}

void EventManager::deregisterComponent(Component &component, Event::EventType eventFlag) {
    ComponentFlagMap::iterator it;

    it = registrationMap.find(&component);
    if (it != registrationMap.end() )
    {
        BitFlags currentflags = it->second;

        for (BitFlags flag = (BitFlags)Event::KeyPressed; flag <= (BitFlags)Event::SocketMessage; flag = flag << 1)
        {
            if (flag & currentflags & eventFlag)
            {
                dispatchMap[(Event::EventType)flag].erase(&component);
                it->second -= flag;
            }
        }

        if (it->second == 0)
            registrationMap.erase(&component);
    }
}

void EventManager::registerComponent(Component& component, Event::EventType eventFlag) {
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

    for( BitFlags flag = (BitFlags)Event::KeyPressed; flag <= (BitFlags)Event::SocketMessage; flag = flag << 1 )
    {
        if (flag & ~currentFlags & eventFlag)
        {
            dispatchMap[(Event::EventType)flag].insert(&component);
            registrationMap[&component] += flag;
        }
    }
}