//
// Created by Brandon Martin on 4/10/19.
//

#ifndef CURSEN_SIMPLEFORM_H
#define CURSEN_SIMPLEFORM_H

#include "Cursen/Components/CheckBox.h"
#include "Cursen/Components/Form.h"
#include "Cursen/Components/Label.h"
#include "Uno/Components/ModeSelectBox.h"
#include <Uno/Components/GiantCard.h>

class SimpleForm : public cursen::Form {

public:

    SimpleForm();
    void initialize() override;

    void keyUp(EVENT_ARG);
    void keyDown(EVENT_ARG);

private:

    cursen::Button hello;
    cursen::Label count;

};


#endif //CURSEN_SIMPLEFORM_H
