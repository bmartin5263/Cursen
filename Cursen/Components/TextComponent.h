//
// Created by Brandon Martin on 4/3/19.
//

#ifndef CURSEN_TEXTCOMPONENT_H
#define CURSEN_TEXTCOMPONENT_H

#include "Components/Component.h"

class TextComponent : public Component {

public:

    TextComponent();
    TextComponent(const Size& pos);
    TextComponent(const Size& pos, const Size& dim);
    ~TextComponent() = default;

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

    void render() override = 0;

    Content * getContent() override;
    void setSize(const Size &size);
    Size getSize();

protected:

    ColorPair& getCurrentDrawColor();

private:

    Content content;
    ColorPair draw_color;
    Color foreground;
    Color background;
    Color highlight_foreground;
    Color highlight_background;
    Color disabled_foreground;
    Color disabled_background;
    bool isHovered;

};


#endif //CURSEN_TEXTCOMPONENT_H
