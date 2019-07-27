//
// Created by Brandon Martin on 4/10/19.
//

#ifndef CURSEN_SIMPLEFORM_H
#define CURSEN_SIMPLEFORM_H

#include "Cursen/Components/CheckBox.h"
#include "Cursen/Components/Form.h"
#include "Cursen/Components/Label.h"
#include "Uno/UnoComponents/ModeSelectBox.h"
#include <Uno/UnoComponents/GiantCard.h>

class SimpleForm : public cursen::Form {

public:

    SimpleForm();
    void initialize() override;

private:

    GiantCard front;
    GiantCard back;

};


#endif //CURSEN_SIMPLEFORM_H
