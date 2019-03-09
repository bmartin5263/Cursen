//
// Created by Brandon Martin on 2/21/19.
//

#ifndef CURSEN_FORM_H
#define CURSEN_FORM_H

#include <string>
#include "Events/Event.h"

class Form {

public:

    void init();
    void keyPress(const Event& event);
    void deletePress(const Event& event);
    void enterPress(const Event& event);
    void hoverComponent();
    void hoverawayComponent();
    void clickComponent();

};


#endif //CURSEN_FORM_H
