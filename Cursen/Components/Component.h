//
// Created by Brandon Martin on 3/8/19.
//

#ifndef CURSEN_COMPONENT_H
#define CURSEN_COMPONENT_H

#include <functional>
#include <vector>
#include <string>

#include "Cursen/Events/Event.h"
#include "Cursen/Drawing/Content.h"

namespace cursen {

    class Form;
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
         * @note Returning a nullptr will cause the TerminalManager to skip over drawing/rendering this component.
         * This is utilized by AggregateComponent.
         */
        //virtual Content * getContent() = 0;

        //virtual void render() = 0;

        // Attributes
        virtual void setEnabled(bool value);
        virtual bool isEnabled() const;
        virtual void enableIf(std::function<bool()> f);

        virtual void setSilenced(bool value);
        virtual bool isSilenced() const;

        void registerTo(Form* form);
        Form* getRegisteredForm();

        // Event Functions

        /**
         * @brief Set the callback for when any key is pressed.
         *
         * @param f Key Press Function
         * @note This method automatically registers this component for Any Key Presses.
         */
        void onAnyKeyPress(std::function<void(const Event &)> f);

        /**
         * @brief Set the callback for when a key is pressed that isn't the escape key, the delete key, an arrow key, or the enter key.
         *
         * @param f Key Press Function
         * @note This method automatically registers this component for Key Presses.
         */
        void onKeyPress(std::function<void(const Event &)> f);

        void onKeyDown(std::function<void(const Event &)> fn);
        void onKeyUp(std::function<void(const Event &)> fn);

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
         virtual void onCursor(std::function<void()> f);

        /**
         * @brief Set the callback for when a Cursor hovers away from this Component
         *
         * @param f Cursor Off Function
         * @sa Cursor
         */
         virtual void offCursor(std::function<void()> f);

        /**
         * @brief Set the callback for when a Cursor 'clicks' on this Component
         *
         * @param f Click Function
         * @sa Cursor
         */
         virtual void onClick(std::function<void()> f);

        /**
         * @brief Set the callback for each update cycle
         *
         * @param f Click Function
         * @sa Cursor
         */
        void onUpdate(std::function<void()> f);

        /**
         * @brief Removes the callback for Any Key Presses and deregisters itself from Key Events
         */
        void detachAnyKeyPress();

        void detachKeyDown();
        void detachKeyUp();

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

        /**
         * @brief Removes the callback enable if
         */
        void detachEnableIf();

        /**
         * @brief Removes the update callback
         */
        void detachUpdate();

        void CallAnyKeyPress(const Event& event) const;
        void CallKeyPress(const Event& event) const;
        void CallEscapePress(const Event& event) const;
        void CallEnterPress(const Event& event) const;
        void CallDeletePress(const Event& event) const;
        void CallArrowPress(const Event& event) const;
        void CallKeyUp(const Event& event) const;
        void CallKeyDown(const Event& event) const;
        void CallOnCursor() const;
        void CallOffCursor() const;
        void CallOnClick() const;

        const std::function<bool()>& GetEnableIf() const;
        const std::function<void()>& GetUpdate() const;

        std::string id;
        void setId(std::string id) { this->id = id; }

        void setParent(Component*);

    private:

        std::function<void(const Event&)> f_keyPress;
        std::function<void(const Event&)> f_keyDown;
        std::function<void(const Event&)> f_keyUp;
        std::function<void(const Event&)> f_anyKeyPress;
        std::function<void(const Event&)> f_escapePress;
        std::function<void(const Event&)> f_enterPress;
        std::function<void(const Event&)> f_deletePress;
        std::function<void(const Event&)> f_arrowPress;

        std::function<void()> f_update;

        /* Cursor Callbacks */
        std::function<void()> f_onCursor;
        std::function<void()> f_offCursor;
        std::function<void()> f_onClick;

        std::function<bool()> f_enableIf;

        Component* parent;
        Form* registeredForm;

        bool enabled;   /// True if Component is active, False if otherwise
        bool silenced;  /// True if Component should not respond to events, False if otherwise
        bool registeredForUpdates;

    };


}

#endif //CURSEN_COMPONENT_H
