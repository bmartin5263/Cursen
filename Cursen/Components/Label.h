//
// Created by Brandon Martin on 3/11/19.
//

#ifndef CURSEN_LABEL_H
#define CURSEN_LABEL_H


#include <Components/Component.h>
#include <string>
#include <Drawing/TextAlignment.h>

using namespace cursen;

class Label : public Component {

public:

    Label(const Vect2i& pos, const Vect2i& dim);

    void initialize() override;
    void render() override;

    void emplaceText(const std::string& text);
    void setText(const std::string& text) override;
    void setColor(const Color& color) override;

    void cursorOn();
    void cursorOff();

    void setEnabled(bool value) override;

private:

    void changeColor(const Color& color);

    std::string text;
    Color foreground;
    Color background;
    Color highlight_color;
    ColorPair draw_color;
    TextAlignment alignment;

};


#endif //CURSEN_LABEL_H
