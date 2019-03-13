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

    virtual void Initialize() = 0;
    virtual void Destroy() = 0;

};


#endif //CURSEN_FORM_H
