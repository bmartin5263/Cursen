//
// Created by Brandon Martin on 2/21/19.
//

#ifndef CURSEN_FORM_H
#define CURSEN_FORM_H

#include <string>
#include "Events/Event.h"
#include "Component.h"
#include "TextComponent.h"
#include "AggregateComponent.h"

using namespace cursen;

class Form : public AggregateComponent {

public:

    Form(const Size& dim);

    Size getSize();

private:

    Size dimensions;

};


#endif //CURSEN_FORM_H
