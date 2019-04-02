//
// Created by Brandon Martin on 3/21/19.
//

#ifndef CURSEN_CLICKABLECOMPONENT_H
#define CURSEN_CLICKABLECOMPONENT_H

#include "Component.h"

class ColorComponent : public Component {

public:

    ColorComponent(const Size& pos, const Size& dim);

    virtual void initialize() override;

    virtual void setForeground(const Color &color) override;
    virtual Color getForeground() override;

    virtual void setBackground(const Color &color) override;
    virtual Color getBackground() override;

    virtual void cursorOn();
    virtual void cursorOff();

    void setEnabled(bool value) override;

    void setHighlight(const ColorPair &color) override;
    ColorPair getHighlight() override;

    void setDisabled(const ColorPair &color) override;
    ColorPair getDisabled() override;

protected:

    ColorPair draw_color;
    Color foreground;
    Color background;
    Color highlight_foreground;
    Color highlight_background;
    Color disabled_foreground;
    Color disabled_background;
    bool isHovered;

};


#endif //CURSEN_CLICKABLECOMPONENT_H
