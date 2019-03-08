//
// Created by Brandon Martin on 3/8/19.
//

#ifndef CURSEN_COMPONENT_H
#define CURSEN_COMPONENT_H

#include <functional>
#include <Events/Event.h>

class Component {

public:

    // Event Functions
    void onKeyPress(std::function<void(const Event &)> f);
    void onEscapePress(std::function<void(const Event &)> f);
    void onEnterPress(std::function<void(const Event &)> f);
    void onSocketMessage(std::function<void(const Event &)> f);
    void onSocketConnect(std::function<void(const Event &)> f);
    void onSocketDisconnect(std::function<void(const Event &)> f);
    void onDeletePress(std::function<void(const Event &)> f);
    void onArrowPress(std::function<void(const Event &)> f);

    // Cursor Functions
    /**
     * Called when a virtual Cursor hovers over this component
     * @param f
     */
    void onCursor(std::function<void(const Event &)> f) {};

    /**
     * Called when a virtual Cursor hovers away from this component
     * @param f
     */
    void offCursor(std::function<void(const Event &)> f) {};

    /**
     * Called when a virtual Cursor clicks on this component
     * @param f
     */
    void onClick(std::function<void(const Event &)> f) {};

private:

    friend class EventManager;

    std::function<void(const Event&)> f_keyPress;
    std::function<void(const Event&)> f_escapePress;
    std::function<void(const Event&)> f_enterPress;
    std::function<void(const Event&)> f_socketMessage;
    std::function<void(const Event&)> f_socketConnect;
    std::function<void(const Event&)> f_socketDisconnect;
    std::function<void(const Event&)> f_deletePress;
    std::function<void(const Event&)> f_arrowPress;

};


#endif //CURSEN_COMPONENT_H
