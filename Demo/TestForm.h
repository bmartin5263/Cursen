//
// Created by Brandon Martin on 3/11/19.
//

#ifndef CURSEN_TESTFORM_H
#define CURSEN_TESTFORM_H


#include <Components/Form.h>
#include <Components/Box.h>
#include <Components/CheckBox.h>
#include <Components/Label.h>
#include <Components/TwirlProgress.h>
#include <Cursor/Cursor.h>
#include <Components/Button.h>

class TestForm : public Form {

public:

    TestForm();

    void initialize() override;
    void keyPress(const Event& event);
    void moveComponent(const Event& event);
    void disable();
    void alarmFunction();
    void activateTwirl();

    void flash();
    void beep();
    void doRainbow();
    void changeColor();
    void quitGame();

private:

    Cursor cursor;
    Button pressMe;
    Label flashLabel;
    Label messageLabel;
    Label beepLabel;
    Label changeColorLabel;
    Label exitLabel;
    Label smileyFace;
    Label label6;
    CheckBox checkBox;
    CheckBox checkBox2;
    CheckBox twirlCheck;
    Box box;
    Box titleBox;
    TwirlProgress twirlProgress;

};


#endif //CURSEN_TESTFORM_H
