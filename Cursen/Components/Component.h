//
// Created by Brandon Martin on 3/8/19.
//

#ifndef CURSEN_COMPONENT_H
#define CURSEN_COMPONENT_H

#include <functional>
#include <Events/Event.h>
#include <vector>
#include <ncurses.h>
#include <Drawing/TextBody.h>
#include <Drawing/ClearRequest.h>

class Component {

public:

    // Construction
    Component();
    Component(const Vect2i& pos);
    Component(const Vect2i& pos, const Vect2i& dim);
    ~Component();

    // Initialization
    virtual void initialize() = 0;

    // Drawing
    void invalidate();
    void validate();
    bool isInvalid();

    virtual void render() = 0;
    void move(const Vect2i& movement);
    TextBody& getTextBody();

    // Component Relationship
    void addComponent(Component*);
    void removeComponent(Component*);
    Component* getParent();

    // Attributes
    virtual void setEnabled(bool value);
    virtual bool isEnabled();

    // Event Functions
    void onKeyPress(std::function<void(const Event &)> f);
    void onEscapePress(std::function<void(const Event &)> f);
    void onEnterPress(std::function<void(const Event &)> f);
    void onSocketMessage(std::function<void(const Event &)> f);
    void onSocketConnect(std::function<void(const Event &)> f);
    void onSocketDisconnect(std::function<void(const Event &)> f);
    void onDeletePress(std::function<void(const Event &)> f);
    void onArrowPress(std::function<void(const Event &)> f);
    void onCursor(std::function<void()> f);
    void offCursor(std::function<void()> f);
    void onClick(std::function<void()> f);
    void detachKeyPress();
    void detachEscapePress();
    void detachEnterPress();
    void detachSocketMessage();
    void detachSocketConnect();
    void detachSocketDisconnect();
    void detachDeletePress();
    void detachArrowPress();
    void detachOnClick();
    void detachOffCursor();
    void detachOnCursor();

private:

    friend class EventManager;
    friend class CursesManager;
    friend class Cursor;

    void CallKeyPress(const Event&);
    void CallEscapePress(const Event&);
    void CallEnterPress(const Event&);
    void CallSocketMessage(const Event&);
    void CallSocketDisconnect(const Event&);
    void CallSocketConnect(const Event&);
    void CallDeletePress(const Event&);
    void CallArrowPress(const Event&);
    void CallOnCursor();
    void CallOffCursor();
    void CallOnClick();

    void setParent(Component*);

    std::function<void(const Event&)> f_keyPress;
    std::function<void(const Event&)> f_escapePress;
    std::function<void(const Event&)> f_enterPress;
    std::function<void(const Event&)> f_socketMessage;
    std::function<void(const Event&)> f_socketConnect;
    std::function<void(const Event&)> f_socketDisconnect;
    std::function<void(const Event&)> f_deletePress;
    std::function<void(const Event&)> f_arrowPress;
    std::function<void()> f_onCursor;
    std::function<void()> f_offCursor;
    std::function<void()> f_onClick;

    Component* parent;
    ClearRequest clearRequest;

protected:

    std::vector<Component*> components;
    TextBody body;
    Vect2i position;
    bool enabled;
    bool invalid;

};


#endif //CURSEN_COMPONENT_H
