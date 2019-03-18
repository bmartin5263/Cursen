//
// Created by Brandon Martin on 2/21/19.
//

#ifndef CURSEN_FORM_H
#define CURSEN_FORM_H

#include <string>
#include "Events/Event.h"
#include "Component.h"

class Form : public Component {

public:

    virtual void initialize() override = 0;

    void render() override;

};


#endif //CURSEN_FORM_H
