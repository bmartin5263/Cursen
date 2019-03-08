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

    if (key == CursesManager::KEY_ESCAPE) {
        event.type = Event::EscPressed;
        event.key.code = key;
    }
    else if (key == CursesManager::KEY_BACKSPACE)
    {
        event.type = Event::DeletePressed;
        event.key.code = key;
    }
    else if (key == CursesManager::KEY_ENTER)
    {
        event.type = Event::EnterPressed;
        event.key.code = key;
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
            for( ComponentList::iterator listItem = componentList.begin(); listItem != componentList.end(); ++listItem) {
                (*listItem)->f_keyPress(event);
            }
            break;
        case Event::EscPressed:
            CursenApplication::Quit();
            break;
        case Event::DeletePressed:
            componentList = dispatchMap[Event::KeyPressed];
            for( ComponentList::iterator listItem = componentList.begin(); listItem != componentList.end(); ++listItem) {
                (*listItem)->f_deletePress(event);
            }
            break;
        case Event::EnterPressed:
            componentList = dispatchMap[Event::KeyPressed];
            for( ComponentList::iterator listItem = componentList.begin(); listItem != componentList.end(); ++listItem) {
                (*listItem)->f_enterPress(event);
            }
            break;
        case Event::SocketConnected:
            componentList = dispatchMap[Event::KeyPressed];
            for( ComponentList::iterator listItem = componentList.begin(); listItem != componentList.end(); ++listItem) {
                (*listItem)->f_socketConnect(event);
            }
            break;
        case Event::SocketDisconnected:
            componentList = dispatchMap[Event::KeyPressed];
            for( ComponentList::iterator listItem = componentList.begin(); listItem != componentList.end(); ++listItem) {
                (*listItem)->f_socketDisconnect(event);
            }
            break;
        case Event::SocketMessage:
            componentList = dispatchMap[Event::KeyPressed];
            for( ComponentList::iterator listItem = componentList.begin(); listItem != componentList.end(); ++listItem) {
                (*listItem)->f_socketMessage(event);
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

        for( BitFlags flag = (BitFlags)Event::KeyPressed; flag <= (BitFlags)Event::SocketMessage; flag = flag << 1 )
        {
            if ( flag & currentflags & eventFlag)
            {
                dispatchMap[ (Event::EventType) flag].erase(&component);
                it->second -= flag;
            }
        }

        if ( it->second == 0)
            registrationMap.erase(&component);
    }
}

void EventManager::registerComponent(Component& component, Event::EventType eventFlag) {
    ComponentFlagMap::iterator it;
    BitFlags currentFlags;

    it = registrationMap.find(&component);
    if (it != registrationMap.end() )
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
        if ( flag & ~currentFlags & eventFlag)
        {
            dispatchMap[ (Event::EventType) flag ].insert(&component);
            registrationMap[&component] += flag;
        }
    }
}