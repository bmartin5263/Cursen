//
// Created by Brandon Martin on 3/8/19.
//

#ifndef CURSEN_COMPONENT_H
#define CURSEN_COMPONENT_H

#include <functional>
#include <Events/Event.h>

class Component {

public:

    Component();

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

    /**
     * Called when a virtual Cursor hovers over this component
     * @param f
     */
    void onCursor(std::function<void()> f);

    /**
     * Called when a virtual Cursor hovers away from this component
     * @param f
     */
    void offCursor(std::function<void()> f);

    /**
     * Called when a virtual Cursor clicks on this component
     * @param f
     */
    void onClick(std::function<void()> f);

private:

    friend class EventManager;
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

protected:

    bool enabled;

};


#endif //CURSEN_COMPONENT_H
