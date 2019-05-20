//
// Created by Brandon Martin on 2/21/19.
//

#include <Drawing/CursesManager.h>
#include <functional>
#include "Form.h"
#include "Component.h"
#include "Cursor/Cursor.h"

Form::Form(const Vect2 &dim) :
        AggregateComponent(Vect2(0,0)), dimensions(dim)
{
    if (dim.x < 1 || dim.y < 1) throw std::logic_error("Form requires dimensions > 0");
}

Vect2 Form::getSize() {
    return dimensions;
}
