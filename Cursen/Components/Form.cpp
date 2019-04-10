//
// Created by Brandon Martin on 2/21/19.
//

#include <Drawing/CursesManager.h>
#include <functional>
#include "Form.h"
#include "Component.h"
#include "Cursor/Cursor.h"

Form::Form(const Size &dim) :
        AggregateComponent(Size(0,0)), dimensions(dim)
{
    if (dim.x < 1 || dim.y < 1) throw std::logic_error("Form requires dimensions > 0");
}

Size Form::getSize() {
    return dimensions;
}
