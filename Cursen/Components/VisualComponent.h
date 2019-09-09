//
// Created by Brandon Martin on 7/27/19.
//

#ifndef CURSEN_VISUALCOMPONENT_H
#define CURSEN_VISUALCOMPONENT_H

#include "Component.h"

namespace cursen
{
    class VisualComponent : public cursen::Component
    {

    public:

        VisualComponent() : Component()
        {}

        VisualComponent(const Vect2& pos) : Component(pos)
        {}

        virtual size_t getDrawOrder() const = 0;
        virtual void setDrawOrder(size_t order) = 0;
        virtual void addDrawOrder(size_t value) = 0;
        virtual void drawOnTopOf(VisualComponent& component) = 0;

        /////////////////////////////////////////////////////////////////////////////////////////////////////
        /**
         * Common Attributes:
         *
         * The following methods provide an interface for editing common elements across most VisualComponents.
         * By Default, these methods provide no meaningful functionality, all subclasses of VisualComponent should
         * override these methods with functionality that makes sense for that Component.
         */
        /////////////////////////////////////////////////////////////////////////////////////////////////////

        virtual void setText(const std::string& text) {};
        virtual std::string getText() const { return ""; };

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
        virtual Color getForeground() const { return Color::NONE; };

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
        virtual Color getBackground() const { return Color::NONE; };

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
        virtual ColorPair getHighlight() const { return ColorPair::NONE; };

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
        virtual ColorPair getDisabled() const { return ColorPair::NONE; };

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

        /**
         * @brief Get the Component's current on-screen position.
         *
         * @return Component's Vector Position
         */
        Vect2 getPosition() const;

        virtual void setPosition(const Vect2& pos);

        virtual void move(const Vect2& movement);

        virtual void setCursable(bool value);
        virtual bool isCursable() const;

    private:

        Vect2 position;
        bool hidden;    /// True if Component should not be drawn, False if otherwise
        bool cursable;  /// True if Cursor should cursor over Component, False if otherwise

    };
}

#endif //CURSEN_VISUALCOMPONENT_H
