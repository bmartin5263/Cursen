//
// Created by Brandon Martin on 3/11/19.
//

#ifndef CURSEN_TESTFORM_H
#define CURSEN_TESTFORM_H


#include <Components/Form.h>

class Label;

class TestForm : public Form {

public:

    void Initialize() override;
    void Destroy() override;

    void keyPress(const Event& event);
    void enterPress(const Event& event);
    void arrowPress(const Event& event);

private:

    Label* c;
    Label* c1;
    Label* c2;
    Label* c3;

};


#endif //CURSEN_TESTFORM_H
