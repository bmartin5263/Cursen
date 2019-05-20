//
// Created by Brandon Martin on 4/10/19.
//

#ifndef CURSEN_SIMPLEFORM_H
#define CURSEN_SIMPLEFORM_H

#include <Components/CheckBox.h>
#include "Components/Form.h"
#include "Components/Label.h"
#include "../Uno/UnoComponents/ModeSelectBox.h"

class SimpleForm : public cursen::Form {

public:

    SimpleForm();
    void initialize() override;

private:

    ModeSelectBox modeSelectBox;

};


#endif //CURSEN_SIMPLEFORM_H
