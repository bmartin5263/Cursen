//
// Created by Brandon Martin on 3/7/19.
//

#ifndef CURSEN_EVENTMANAGER_H
#define CURSEN_EVENTMANAGER_H

#include <unordered_map>
#include <unordered_set>
#include "Event.h"

class Component;

class EventManager {

public:

    static Event PollEvent() { return Instance().pollEvent(); };
    static void ProcessEvent(Event& event) { Instance().processEvent(event); }

    static void Register(Component& component, Event::EventType events) { Instance().registerComponent(component, events); }
    static void Deregister(Component& component, Event::EventType events) { Instance().deregisterComponent(component, events); }

private:

    typedef int BitFlags;
    typedef std::unordered_map<Component*, BitFlags> ComponentFlagMap;
    typedef std::unordered_set<Component*> ComponentList;
    typedef std::unordered_map<Event::EventType, ComponentList, EnumClassHash> FlagListMap;

    // Methods
    Event pollEvent();
    void processEvent(Event& event);
    void registerComponent(Component& component, Event::EventType eventFlag);
    void deregisterComponent(Component& component, Event::EventType events);

    // Instance Data
    FlagListMap dispatchMap;
    ComponentFlagMap registrationMap;

    // Static Data

    static EventManager* instance;

    static EventManager& Instance() {
        if (instance == nullptr)
            instance = new EventManager;
        return *instance;
    }

    EventManager() = default;
    EventManager(const EventManager& other) = delete;
    EventManager(EventManager&& other) noexcept = delete;
    EventManager& operator = (const EventManager& other) = delete;
    EventManager& operator = (EventManager&& other) = delete;
    ~EventManager();

};


#endif //CURSEN_EVENTMANAGER_H
