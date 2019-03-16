//
// Created by Brandon Martin on 3/11/19.
//

#ifndef CURSEN_LABEL_H
#define CURSEN_LABEL_H


#include <Components/Component.h>
#include <Components/TextComponent.h>
#include <string>
#include <Drawing/TextAlignment.h>

using namespace cursen;

class Label : public TextComponent {

public:

    Label(const Vect2d& pos, const Vect2d& dim);

    void initialize() override;
    void destroy() override;
    void draw() override;

    void emplaceText(const std::string& text);
    void setText(const std::string& text);

private:

    std::string text;
    TextAlignment alignment;

};


#endif //CURSEN_LABEL_H
