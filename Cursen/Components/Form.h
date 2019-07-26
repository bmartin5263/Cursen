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
#include <queue>

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
        typedef std::queue<Alarm*> AlarmQueue;
        typedef std::queue<unsigned int> IntQueue;
        typedef std::function<void()> VoidFunction;

    public:

        Form(const Vect2& dim);

        Vect2 getSize();

        void registerComponent(TextComponent* component);
        void deregisterComponent(TextComponent* component);
        void setComponentDrawOrder(TextComponent* component, size_t order);

        void registerCursor(Cursor* cursor);
        void deregisterCursor(Cursor* cursor);

        void registerForEvents(Component* component, EventType events);
        void deregisterForEvents(Component* component, EventType events);

        void closeForm();
        void openForm(Form* form);

        virtual void onOpen(VoidFunction f);
        virtual void onClose(VoidFunction f);

        void detachOnOpen();
        void detachOnClose();

        void CallOnOpen();
        void CallOnClose();

        CursorSet& getCursors();
        ComponentMap& getComponentDrawMap();
        AlarmMap& getAlarmMap();
        EventComponentMap& getEventDispatchMap();
        ComponentRegistrationMap& getEventRegistrationMap();
        AlarmQueue& getStartRequests();
        IntQueue& getStopRequests();

    private:

        VoidFunction fOpen;
        VoidFunction fClose;

        CursorSet cursors;
        ComponentMap componentDrawMap;
        AlarmMap alarmMap;
        AlarmQueue startRequests;       /// Queue for requests to start Alarms
        IntQueue stopRequests;          /// Queue for requests to cancel Alarms
        EventComponentMap dispatchMap;
        ComponentRegistrationMap eventRegistrationMap;

        Vect2 dimensions;

    };

}

#endif //CURSEN_FORM_H
