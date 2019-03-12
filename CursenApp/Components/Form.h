//
// Created by Brandon Martin on 2/21/19.
//

#ifndef CURSEN_FORM_H
#define CURSEN_FORM_H

#include <string>
#include "Events/Event.h"
#include "Component.h"

class Form {

public:

    void Initialize();
    void Destroy();
    void clickComponent();
    void arrowPress(const Event& e);

    Component* c;

};


#endif //CURSEN_FORM_H
