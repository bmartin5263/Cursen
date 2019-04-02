//
// Created by Brandon Martin on 3/11/19.
//

#ifndef CURSEN_LABEL_H
#define CURSEN_LABEL_H


#include <Components/Component.h>
#include <string>
#include <Drawing/TextAlignment.h>
#include "ColorComponent.h"

using namespace cursen;

class Label : public ColorComponent {

public:

    Label(const Size& pos, const Size& dim);

    void initialize() override;
    void render() override;

    void emplaceText(const std::string& text);
    void setText(const std::string& text) override;



private:

    std::string text;
    TextAlignment alignment;

};


#endif //CURSEN_LABEL_H
