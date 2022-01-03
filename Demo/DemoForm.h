//
// Created by Brandon on 12/24/21.
//

#ifndef CURSEN_DEMOFORM_H
#define CURSEN_DEMOFORM_H


#include "Cursen/Components/Form.h"
#include "Cursen/Components/Button.h"
#include "Cursen/Components/Label.h"
#include "Cursen/Cursor/Cursor.h"
#include "Cursen/Components/CheckBox.h"

class DemoForm : public cursen::Form {
public:
    DemoForm();
    void initialize() override;
private:
    cursen::Cursor cursor;
    cursen::Label label;
    cursen::Button button;
    cursen::CheckBox checkBox;
};

#endif //CURSEN_DEMOFORM_H
