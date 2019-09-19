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
        typedef std::function<void(void*)> CloseFunction;

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

        void close(void* return_value);
        void open(Form* form);

        // Open is called when this form returns to the top of the form stack
        virtual void onOpen(VoidFunction f);

        // Closed is called after this form is removed from the top of the form stack but not yet
        // deleted. Intended to be used by the parent form to check for return codes.
        virtual void onClosed(CloseFunction f);

        // Called before the form is removed from the top of the form stack. Intended to be used
        // to do any sort of cleanup.
        virtual void beforeClosing(VoidFunction f);

        void detachOnOpen();
        void detachOnClosed();
        void detachBeforeClosing();

        void CallOnOpen();
        void CallOnClosed(void* return_value);
        void CallBeforeClosing();

        CursorSet& getCursors();
        ComponentMap& getComponentDrawMap();
        AlarmMap& getAlarmMap();
        EventComponentMap& getEventDispatchMap();
        ComponentRegistrationMap& getEventRegistrationMap();
        AlarmQueue& getStartRequests();
        IntQueue& getStopRequests();

    private:

        Vect2 dimensions;

        VoidFunction fOpen;
        VoidFunction fBeforeClose;
        CloseFunction fClose;

        CursorSet cursors;
        ComponentMap componentDrawMap;
        AlarmMap alarmMap;
        AlarmQueue startRequests;       /// Queue for requests to start Alarms
        IntQueue stopRequests;          /// Queue for requests to cancel Alarms
        EventComponentMap dispatchMap;
        ComponentRegistrationMap eventRegistrationMap;


    };

}

#endif //CURSEN_FORM_H
