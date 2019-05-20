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
#include <Drawing/Content.h>

class Component {

public:

    // Construction
    Component();
    Component(const Vect2& pos);
    virtual ~Component();

    virtual void initialize() = 0;

    // Drawing
    /**
     * @brief Get the textual content that makes up the visuals of the Component
     *
     * The drawing engine uses the data structure 'Content' in order to draw the Component
     * onto the terminal. The base class Component does not contain any Content data member since
     * some Components, 'AggregateComponents', do not draw any content themselves but rather combine
     * other Components together which do have textual content. Thus, this method is left abstract.
     *
     * Any component that intends on drawing text to the terminal should inherit from 'TextComponent',
     * which implements this method.
     *
     * @return Pointer to this Component's Content
     *
     * @note Returning a nullptr will cause the CursesManager to skip over drawing/rendering this component.
     * This is utilized by AggregateComponent.
     */
    virtual Content * getContent() = 0;

    /**
     * @brief Get the draw order for this Component
     *
     * @return Draw Order
     */
    int getDrawOrder();

    /**
     * @brief Set the draw order for this Component
     *
     * @param order New Draw Order
     */
    void setDrawOrder(int order);

    /**
     * @brief Sets 'invalid' flag to True, causing Component to be re-rendered next Screen Draw
     *
     * Whenever any visual data is changed for the Component this method should be called.
     */
    void invalidate();

    /**
     * @brief Sets 'invalid' flag to False, preventing Component from being re-rendered next Screen Draw
     *
     * This method is called by CursesManager after it is done with rendering the Component.
     */
    void validate();

    /**
     * @brief Tells if this Component is invalid and needs to be re-rendered.
     *
     * This method is called by CursesManager to check if it needs to re-render this Component.
     */
    bool isInvalid();

    virtual void render() = 0;
    Vect2 getPosition() const;
    virtual void setPosition(const Vect2& pos);
    virtual void move(const Vect2& movement);

    // Component Relationship
    void add(Component *);
    void addRelative(Component *);
    void remove(Component *);
    Component* getParent();
    const std::vector<Component*> & getChildren();

    // Attributes
    virtual void setEnabled(bool value);
    virtual bool isEnabled() const;

    virtual void setSilenced(bool value);
    virtual bool isSilenced();

    virtual void setCursable(bool value);
    virtual bool isCursable();

    /**
     * @brief Enable or Disable drawing of this Component
     *
     * @param value True to hide component, False to show component
     */
    virtual void setHidden(bool value);

    /**
     * @brief Tell whether the Component is hidden or not
     *
     * @return True if Component is hidden, False if otherwise
     */
    virtual bool isHidden() const;

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    /**
     * Common Attributes:
     *
     * The following methods provide an interface for editing common elements across most Components.
     * By Default, these methods provide no meaningful functionality, all subclasses of Component should
     * override these methods with functionality that makes sense for that Component.
     */
    /////////////////////////////////////////////////////////////////////////////////////////////////////

    /**
     * @brief Set the Foreground Color of the Component
     *
     * @param color Foreground Color
     *
     * @note This method is purposely stubbed out to perform no meaningful action. All subclassed
     * of Component should override this in a manner that makes sense for that Component's
     * function.
     */
    virtual void setForeground(const Color &color) {};

    /**
     * @brief Get the Foreground Color of the Component
     *
     * @returns Foreground Color
     *
     * @note This method is purposely stubbed out to perform no meaningful action. All subclassed
     * of Component should override this in a manner that makes sense for that Component's
     * function.
     */
    virtual Color getForeground() { return Color::NONE; };

    /**
     * @brief Set the Background Color of the Component
     *
     * @returns Background Color
     *
     * @note This method is purposely stubbed out to perform no meaningful action. All subclassed
     * of Component should override this in a manner that makes sense for that Component's
     * function.
     */
    virtual void setBackground(const Color &color) {};

    /**
     * @brief Get the Background Color of the Component
     *
     * @param color Background Color
     *
     * @note This method is purposely stubbed out to perform no meaningful action. All subclassed
     * of Component should override this in a manner that makes sense for that Component's
     * function.
     */
    virtual Color getBackground() { return Color::NONE; };

    /**
     * @brief Set the ColorPair to be used for when a Cursor highlights this Component
     *
     * @param colorPair Highlight ColorPair
     *
     * @note This method is purposely stubbed out to perform no meaningful action. All subclassed
     * of Component should override this in a manner that makes sense for that Component's
     * function.
     */
    virtual void setHighlight(const ColorPair &colorPair) {};

    /**
     * @brief Get the ColorPair used for when a Cursor highlights this Component
     *
     * @returns Highlight ColorPair
     *
     * @note This method is purposely stubbed out to perform no meaningful action. All subclassed
     * of Component should override this in a manner that makes sense for that Component's
     * function.
     */
    virtual ColorPair getHighlight() { return ColorPair::NONE; };

    /**
     * @brief Set the ColorPair to be used for when this Component is disabled.
     *
     * @param colorPair Disabled ColorPair
     *
     * @note This method is purposely stubbed out to perform no meaningful action. All subclassed
     * of Component should override this in a manner that makes sense for that Component's
     * function.
     */
    virtual void setDisabled(const ColorPair &color) {};

    /**
     * @brief Get the ColorPair used for when this Component is disabled.
     *
     * @returns Disabled ColorPair
     *
     * @note This method is purposely stubbed out to perform no meaningful action. All subclassed
     * of Component should override this in a manner that makes sense for that Component's
     * function.
     */
    virtual ColorPair getDisabled() { return ColorPair::NONE; };

    virtual void setText(const std::string& text) {};
    virtual std::string getText() { return ""; };

    // Event Functions

    /**
     * @brief Set the callback for when a key is pressed.
     *
     * @param f Key Press Function
     * @note This method automatically registers this component for Key Presses.
     */
    void onKeyPress(std::function<void(const Event &)> f);

    /**
     * @brief Set the callback for when escape is pressed.
     *
     * @param f Escape Press Function
     * @note This method automatically registers this component for Escape Presses.
     */
    void onEscapePress(std::function<void(const Event &)> f);

    /**
     * @brief Set the callback for when enter is pressed.
     *
     * @note If the Program is making use of the 'Cursor' Component, it is recommended that
     * Components do not use 'onEnterPress' or 'onArrowPress' as Cursor uses both these
     * callbacks for navigation and clicks. This can cause irregular behavior if multiple
     * Components are registered to these events.
     *
     * @param f Enter Press Function
     * @note This method automatically registers this component for Enter Presses.
     */
    void onEnterPress(std::function<void(const Event &)> f);

    void onSocketMessage(std::function<void(const Event &)> f);
    void onSocketConnect(std::function<void(const Event &)> f);
    void onSocketDisconnect(std::function<void(const Event &)> f);

    /**
     * @brief Set the callback for when delete is pressed.
     *
     * @param f Delete Press Function
     * @note This method automatically registers this component for Delete Presses.
     */
    void onDeletePress(std::function<void(const Event &)> f);

    /**
     * @brief Set the callback for when an arrow key is pressed.
     *
     * @note If the Program is making use of the 'Cursor' Component, it is recommended that
     * Components do not use 'onEnterPress' or 'onArrowPress' as Cursor uses both these
     * callbacks for navigation and clicks. This can cause irregular behavior if multiple
     * Components are registered to these events.
     *
     * @param f Arrow Press Function
     * @note This method automatically registers this component for Arrow Key Presses.
     */
    void onArrowPress(std::function<void(const Event &)> f);

    /**
     * @brief Set the callback for when a Cursor hovers over this Component
     *
     * @param f Cursor On Function
     * @sa Cursor
     */
    void onCursor(std::function<void()> f);

    /**
     * @brief Set the callback for when a Cursor hovers away from this Component
     *
     * @param f Cursor Off Function
     * @sa Cursor
     */
    void offCursor(std::function<void()> f);

    /**
     * @brief Set the callback for when a Cursor 'clicks' on this Component
     *
     * @param f Click Function
     * @sa Cursor
     */
    void onClick(std::function<void()> f);

    /**
     * @brief Removes the callback for Key Presses and deregisters itself from Key Events
     */
    void detachKeyPress();

    /**
     * @brief Removes the callback for Escape Presses and deregisters itself from Escape Events
     */
    void detachEscapePress();

    /**
     * @brief Removes the callback for Enter Presses and deregisters itself from Enter Events
     */
    void detachEnterPress();

    void detachSocketMessage();
    void detachSocketConnect();
    void detachSocketDisconnect();

    /**
     * @brief Removes the callback for Delete Presses and deregisters itself from Delete Events
     */
    void detachDeletePress();

    /**
     * @brief Removes the callback for Arrow Presses and deregisters itself from Arrow Events
     */
    void detachArrowPress();

    /**
     * @brief Removes the callback for Click events
     */
    void detachOnClick();

    /**
     * @brief Removes the callback for hover away events
     */
    void detachOffCursor();

    /**
     * @brief Removes the callback for hover on events
     */
    void detachOnCursor();

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

private:

    friend class EventManager;
    friend class CursesManager;
    friend class Cursor;

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
    std::vector<Component*> children;
    Vect2 position;
    int drawOrder;

    bool enabled;   /// True if Component is active, False if otherwise
    bool invalid;   /// True if Component needs to be re-rendered, False if otherwise
    bool hidden;    /// True if Component should not be drawn, False if otherwise
    bool silenced;  /// True if Component should not respond to events, False if otherwise
    bool cursable;  /// True if Cursor should cursor over Component, False if otherwise

};


#endif //CURSEN_COMPONENT_H
