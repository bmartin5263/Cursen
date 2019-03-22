//
// Created by Brandon Martin on 3/11/19.
//

#ifndef CURSEN_TESTFORM_H
#define CURSEN_TESTFORM_H


#include <Components/Form.h>
#include <Components/Box.h>

class Label;
class CheckBox;

class TestForm : public Form {

public:

    TestForm();

    void initialize() override;
    void keyPress(const Event& event);
    void enterPress(const Event& event);
    void arrowPress(const Event& event);
    void moveComponent(const Event& event);
    void disable();

    void flash();
    void beep();
    void changeColor();
    void quitGame();

    void render() override;

private:

    Cursor* cursor;
    Label* flashLabel;
    Label* messageLabel;
    Label* beepLabel;
    Label* changeColorLabel;
    Label* exitLabel;
    Label* smileyFace;
    Label* label6;
    CheckBox* checkBox;
    Box* box;
    Box* titleBox;

};


#endif //CURSEN_TESTFORM_H
