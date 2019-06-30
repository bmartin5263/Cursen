//
// Created by Brandon Martin on 2/21/19.
//

#ifndef CURSEN_FORM_H
#define CURSEN_FORM_H

#include <string>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <map>

#include "Cursen/Events/Event.h"
#include "Component.h"
#include "TextComponent.h"
#include "AggregateComponent.h"

namespace cursen {

    class Cursor;

    class Form : public AggregateComponent {

    private:

        typedef int BitFlags;
        typedef std::unordered_set<Component*> ComponentList;
        typedef std::map<int, std::set<TextComponent*>> ComponentMap;
        typedef std::unordered_set<Cursor*> CursorSet;
        typedef std::unordered_map<unsigned int, Alarm*> AlarmMap;
        typedef std::unordered_map<Component*, BitFlags> ComponentRegistrationMap;
        typedef std::unordered_map<EventType, ComponentList, EnumClassHash> EventComponentMap;

    public:

        Form(const Vect2& dim);

        Vect2 getSize();

        void registerComponent(TextComponent* component);
        void deregisterComponent(TextComponent* component);
        void setDrawOrder(TextComponent* component, int order);

        void registerCursor(Cursor* cursor);
        void deregisterCursor(Cursor* cursor);

        void registerForEvents(Component* component, EventType events);
        void deregisterForEvents(Component* component, EventType events);

        CursorSet& getCursors();
        ComponentMap& getComponentDrawMap();
        AlarmMap& getAlarmMap();
        EventComponentMap& getDispatchMap();
        ComponentRegistrationMap& getEventRegistrationMap();

    private:

        CursorSet cursors;
        ComponentMap componentDrawMap;
        AlarmMap alarmMap;
        EventComponentMap dispatchMap;
        ComponentRegistrationMap eventRegistrationMap;

        Vect2 dimensions;

    };

}

#endif //CURSEN_FORM_H
