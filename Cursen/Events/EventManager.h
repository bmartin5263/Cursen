//
// Created by Brandon Martin on 3/7/19.
//

#ifndef CURSEN_EVENTMANAGER_H
#define CURSEN_EVENTMANAGER_H

#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <thread>

#include "Event.h"
#include "EventType.h"
#include "EventQueue.h"

namespace cursen {

    class Component;

    class EventManager {

    private:

        typedef int BitFlags;
        typedef std::unordered_set<Component*> ComponentList;
        typedef std::unordered_map<Component*, BitFlags> ComponentRegistrationMap;
        typedef std::unordered_map<EventType, ComponentList, EnumClassHash> EventComponentMap;

    public:

        static void ProcessEvents(EventComponentMap& dispatchMap);

        static void PushEvent(Event e) { Instance().eventQueue.push(e); }

        static void Register(Component& component, EventType events) { Instance().registerComponent(component, events); }
        static void Deregister(Component& component, EventType events) { Instance().deregisterComponent(component, events); }

        static EventQueue* GetEventQueue() { return &Instance().eventQueue; }

    private:

        // Methods
        void processUpdates(EventComponentMap& dispatchMap);
        void privProcessEvent(EventComponentMap& dispatchMap, const Event &event);
        void registerComponent(Component& component, EventType eventFlag);
        void deregisterComponent(Component& component, EventType events);
        void processEvents(EventComponentMap& dispatchMap);

        // Instance Data
        EventQueue eventQueue;

        // Static Data

        friend class CursenApplication;
        static EventManager& Instance();

        EventManager() = default;
        EventManager(const EventManager& other) = delete;
        EventManager(EventManager&& other) noexcept = delete;
        EventManager& operator = (const EventManager& other) = delete;
        EventManager& operator = (EventManager&& other) = delete;
        ~EventManager() = default;

    };

}


#endif //CURSEN_EVENTMANAGER_H
