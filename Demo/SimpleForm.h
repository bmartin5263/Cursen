//
// Created by Brandon Martin on 4/10/19.
//

#ifndef CURSEN_SIMPLEFORM_H
#define CURSEN_SIMPLEFORM_H

#include <Components/CheckBox.h>
#include "Components/Form.h"
#include "Components/Label.h"

class SimpleForm : public Form {

public:

    SimpleForm();
    void initialize() override;

private:

    Label l1;
    Label l2;
    CheckBox c;

};


#endif //CURSEN_SIMPLEFORM_H
