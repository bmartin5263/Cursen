//
// Created by Brandon Martin on 2/21/19.
//

#ifndef CURSEN_FORM_H
#define CURSEN_FORM_H

#include <string>
#include "Events/Event.h"
#include "Component.h"

using namespace cursen;

class Form : public Component {

public:

    Form(const Vect2i& dim);

    virtual void initialize() override = 0;
    void render() override = 0;

protected:


};


#endif //CURSEN_FORM_H
