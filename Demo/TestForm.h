//
// Created by Brandon Martin on 3/11/19.
//

#ifndef CURSEN_TESTFORM_H
#define CURSEN_TESTFORM_H


#include <Components/Form.h>
#include <Components/Box.h>

class Label;

class TestForm : public Form {

public:

    void initialize() override;
    void keyPress(const Event& event);
    void enterPress(const Event& event);
    void arrowPress(const Event& event);
    void moveComponent(const Event& event);

    void flash();
    void beep();
    void changeColor();
    void quitGame();

private:

    Cursor* cursor;
    Label* label1;
    Label* label2;
    Label* label3;
    Label* label4;
    Box* box;

};


#endif //CURSEN_TESTFORM_H
