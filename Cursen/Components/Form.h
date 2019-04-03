//
// Created by Brandon Martin on 2/21/19.
//

#ifndef CURSEN_FORM_H
#define CURSEN_FORM_H

#include <string>
#include "Events/Event.h"
#include "Component.h"
#include "TextComponent.h"

using namespace cursen;

class Form : public TextComponent {

public:

    Form(const Size& dim);

    virtual void initialize() override = 0;
    void render() override = 0;

protected:


};


#endif //CURSEN_FORM_H
