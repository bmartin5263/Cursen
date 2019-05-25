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
    class SoloRegistrationKey;

    class EventManager {

    public:

        static void Terminate();

        static Event PollEvent() { return Instance().privPollEvent(); };
        static void ProcessEvent(const Event& event) { Instance().privProcessEvent(event); }

        static void ProcessEvents() { Instance().privProcessEvents(); }

        static void PushEvent(Event e) { Instance().privPushEvent(e); }

        static void Register(Component& component, EventType events) { Instance().registerComponent(component, events); }
        static void Deregister(Component& component, EventType events) { Instance().deregisterComponent(component, events); }

        static SoloRegistrationKey* RegisterSolo(Component& component, EventType events) { return Instance().registerComponentSolo(component, events); }
        static void DeregisterSolo(SoloRegistrationKey* key, EventType events) { Instance().deregisterComponentSolo(key, events); }

        static EventQueue* GetEventQueue() { return Instance().privGetEventQueue(); }

    private:

        typedef int BitFlags;
        typedef std::unordered_set<Component*> ComponentList;
        typedef std::unordered_map<Component*, BitFlags> ComponentRegistrationMap;
        typedef std::unordered_map<EventType, ComponentList, EnumClassHash> EventComponentMap;

        // Methods
        void processUpdates();
        Event privPollEvent();
        void privProcessEvent(const Event &event);
        void registerComponent(Component& component, EventType eventFlag);
        SoloRegistrationKey* registerComponentSolo(Component& component, EventType eventFlag);
        void deregisterComponent(Component& component, EventType events);
        void deregisterComponentSolo(SoloRegistrationKey* key, EventType events);
        void privPushEvent(Event e);
        void privProcessEvents();
        EventQueue* privGetEventQueue();

        // Instance Data
        EventComponentMap dispatchMap;
        ComponentRegistrationMap registrationMap;
        EventQueue eventQueue;

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
        ~EventManager() = default;

    };

}


#endif //CURSEN_EVENTMANAGER_H
