//
// Created by Brandon Martin on 3/11/19.
//

#ifndef CURSEN_TESTFORM_H
#define CURSEN_TESTFORM_H


#include "Cursen/Components/Form.h"
#include "Cursen/Components/Box.h"
#include "Cursen/Components/CheckBox.h"
#include "Cursen/Components/Label.h"
#include "Cursen/Components/TwirlProgress.h"
#include "Cursen/Cursor/Cursor.h"
#include "Cursen/Components/Button.h"
#include "Cursen/Drawing/Animation.h"
#include "Uno/Components/UnoConsole.h"

class TestForm : public cursen::Form {

public:

    TestForm();

    void initialize() override;
    void keyPress(EVENT_ARG);
    void moveComponent(EVENT_ARG);
    void disable();
    void activateTwirl();

    void flash();
    void beep();
    void doRainbow();
    void quitGame();

private:

    cursen::Animation rainbow;
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

    UnoTitle title;

};


#endif //CURSEN_TESTFORM_H
