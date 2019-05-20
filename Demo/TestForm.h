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

class TestForm : public cursen::Form {

public:

    TestForm();

    void initialize() override;
    void keyPress(const cursen::Event& event);
    void moveComponent(const cursen::Event& event);
    void disable();
    void alarmFunction();
    void activateTwirl();

    void flash();
    void beep();
    void doRainbow();
    void changeColor();
    void quitGame();

private:

    cursen::Cursor cursor;
    cursen::Button pressMe;
    cursen::Label flashLabel;
    cursen::Label messageLabel;
    cursen::Label beepLabel;
    cursen::Label changeColorLabel;
    cursen::Label exitLabel;
    cursen::Label smileyFace;
    cursen::Label label6;
    cursen::CheckBox checkBox;
    cursen::CheckBox checkBox2;
    cursen::CheckBox twirlCheck;
    cursen::Box box;
    cursen::Box titleBox;
    cursen::TwirlProgress twirlProgress;

};


#endif //CURSEN_TESTFORM_H
