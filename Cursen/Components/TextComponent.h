//
// Created by Brandon Martin on 4/3/19.
//

#ifndef CURSEN_TEXTCOMPONENT_H
#define CURSEN_TEXTCOMPONENT_H

#include "Cursen/Components/Component.h"

namespace cursen {

    class TextComponent : public Component {

    public:

        TextComponent();
        TextComponent(const Vect2& pos);
        TextComponent(const Vect2& pos, const Vect2& dim);
        ~TextComponent() = default;

        virtual void initialize() override;

        virtual void setForeground(const Color &color) override;
        virtual Color getForeground() override;

        virtual void setBackground(const Color &color) override;
        virtual Color getBackground() override;

        ColorPair& getCurrentDrawColor();

        virtual void cursorOn();
        virtual void cursorOff();

        void setEnabled(bool value) override;

        void setHighlight(const ColorPair &color) override;
        ColorPair getHighlight() override;

        void setDisabled(const ColorPair &color) override;
        ColorPair getDisabled() override;

        Content * getContent() override;

        virtual void setSize(const Vect2 &size);
        Vect2 getSize();

        void startGlow();
        void stopGlow();
        void animateGlow();

        void render() override;

    private:

        Content content;
        ColorPair draw_color;
        Color foreground;
        Color background;
        Color highlight_foreground;
        Color highlight_background;
        Color disabled_foreground;
        Color disabled_background;
        int glow_frame;
        bool isHovered;

    };


}

#endif //CURSEN_TEXTCOMPONENT_H
