//
// Created by Brandon Martin on 3/8/19.
//

#ifndef CURSEN_COMPONENT_H
#define CURSEN_COMPONENT_H

#include <functional>
#include <Events/Event.h>
#include <vector>
#include <string>
#include <ncurses.h>
#include <Drawing/TextBody.h>

class Component {

public:

    // Construction
    Component();
    Component(const Size& pos);
    Component(const Size& pos, const Size& dim);
    virtual ~Component();

    // Initialization
    virtual void initialize() = 0;

    // Drawing
    void invalidate();
    void validate();
    bool isInvalid();
    virtual void render() = 0;
    TextBody& getTextBody();

    // Component Relationship
    void add(Component *);
    void addRelative(Component *);
    void remove(Component *);
    Component* getParent();

    // Attributes
    virtual void setEnabled(bool value);
    virtual bool isEnabled();
    virtual void setHidden(bool value);
    virtual bool isHidden();

    // Common Attributes
    virtual void setForeground(const Color &color) {};
    virtual void setForegroundAll(const Color &color);
    virtual Color getForeground() { return Color::NONE; };

    virtual void setBackground(const Color &color) {};
    virtual void setBackgroundAll(const Color &color);
    virtual Color getBackground() { return Color::NONE; };

    virtual void setHighlight(const ColorPair &color) {};
    virtual void setHighlightAll(const ColorPair &color);
    virtual ColorPair getHighlight() { return ColorPair::NONE; };

    virtual void setDisabled(const ColorPair &color) {};
    virtual void setDisabledAll(const ColorPair &color);
    virtual ColorPair getDisabled() { return ColorPair::NONE; };

    virtual void setText(const std::string& text) {};
    virtual std::string getText() { return ""; };

    Size getDimensions();
    Size getPosition();
    virtual void setPosition(const Size& pos);
    virtual void setSize(const Size& size);
    void move(const Size& movement);

    // Debug
    void enableDebugging();
    void disableDebugging();

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

protected:

    std::vector<Component*> components;
    TextBody content;
    Size position;
    bool enabled;
    bool invalid;
    bool hidden;
    bool debug_coordinates;

};


#endif //CURSEN_COMPONENT_H
