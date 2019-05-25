//
// Created by Brandon Martin on 5/21/19.
//

#ifndef CURSEN_STANDARDCOMPONENT_H
#define CURSEN_STANDARDCOMPONENT_H


#include <Cursen/Drawing/Animation.h>
#include "Cursen/Components/Component.h"
#include "TextComponent.h"

namespace cursen {

    class StandardComponent : public TextComponent {

    public:

        StandardComponent();
        StandardComponent(const Vect2& pos);
        StandardComponent(const Vect2& pos, const Vect2& dim);
        ~StandardComponent();

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

        virtual void render() override;

        void startGlow();
        void stopGlow();

    private:

        Animation animation;
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


#endif //CURSEN_STANDARDCOMPONENT_H
