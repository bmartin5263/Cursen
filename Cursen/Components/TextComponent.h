//
// Created by Brandon Martin on 4/3/19.
//

#ifndef CURSEN_TEXTCOMPONENT_H
#define CURSEN_TEXTCOMPONENT_H

#include "VisualComponent.h"

namespace cursen {

    class TextComponent : public VisualComponent {

    public:

        TextComponent();
        TextComponent(const Vect2& pos);
        TextComponent(const Vect2& pos, const Vect2& dim);
        ~TextComponent();

        virtual void initialize() override;

        virtual void render() = 0;

        /**
         * @brief Sets 'invalid' flag to True, causing Component to be re-rendered next Screen Draw
         *
         * Whenever any visual data is changed for the Component this method should be called.
         */
        void invalidate();

        /**
         * @brief Sets 'invalid' flag to False, preventing Component from being re-rendered next Screen Draw
         *
         * This method is automatically called by CursesManager after it is done with rendering the Component.
         */
        void validate();

        /**
         * @brief Tells if this Component is invalid and needs to be re-rendered.
         *
         * This method is called by CursesManager to check if it needs to re-render this Component.
         */
        bool isInvalid() const;

        virtual void setSize(const Vect2 &size);
        virtual Vect2 getSize() const;

        virtual Content& getContent();
        virtual const Content& getContentConst() const;
        size_t getDrawOrder() const override;
        void setDrawOrder(size_t order) override;
        void addDrawOrder(size_t value) override;
        void drawOnTopOf(VisualComponent& component) override;
        void setPosition(const Vect2& pos) override;
        void move(const Vect2& movement) override;

    private:

        Content content;
        size_t order;
        bool invalid;   /// True if Component needs to be re-rendered, False if otherwise

    };
}

#endif //CURSEN_TEXTCOMPONENT_H
