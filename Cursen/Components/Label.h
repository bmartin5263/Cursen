//
// Created by Brandon Martin on 3/11/19.
//

#ifndef CURSEN_LABEL_H
#define CURSEN_LABEL_H


#include <Components/Component.h>
#include <string>
#include <Drawing/TextAlignment.h>
#include "TextComponent.h"

using namespace cursen;

class Label : public TextComponent {

public:

    Label();
    Label(const Size& pos, const Size& dim);

    void initialize() override;
    void render() override;

    void emplaceText(const std::string& text);
    void setText(const std::string& text) override;

    void startGlow();
    void stopGlow();

    void animate_glow();


private:

    std::string text;
    TextAlignment alignment;
    int glow_frame;

};


#endif //CURSEN_LABEL_H
