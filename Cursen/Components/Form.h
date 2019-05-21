//
// Created by Brandon Martin on 2/21/19.
//

#ifndef CURSEN_FORM_H
#define CURSEN_FORM_H

#include <string>

#include "Cursen/Events/Event.h"
#include "Component.h"
#include "TextComponent.h"
#include "AggregateComponent.h"

namespace cursen {

    class Form : public AggregateComponent {

    public:

        Form(const Vect2& dim);

        Vect2 getSize();

    private:

        Vect2 dimensions;

    };

}

#endif //CURSEN_FORM_H
