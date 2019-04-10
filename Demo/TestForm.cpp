//
// Created by Brandon Martin on 3/11/19.
//

#include "Drawing/CursesManager.h"
#include "CursenApplication.h"
#include "Events/AlarmManager.h"
#include "TestForm.h"

TestForm::TestForm() :
    Form(Size(70,33))
{

}

void TestForm::initialize() {
    setHidden(true);

    box.initialize();
    box.setPosition(Size(2,3));
    box.setSize(Size(21, 10));
    add(&box);

    titleBox.initialize();
    titleBox.setPosition(Size(0,0));
    titleBox.setSize(Size(getSize().x, 3));
    titleBox.setLowerRight(ACS_RTEE);
    titleBox.setLowerLeft(ACS_LTEE);
    add(&titleBox);

    flashLabel.initialize();
    flashLabel.setPosition(Size(1,1));
    //flashLabel.setSize(Size(40,1));
    flashLabel.setText("Flash");
    flashLabel.onClick(std::bind(&TestForm::flash, this));

    beepLabel.initialize();
    beepLabel.setPosition(Size(1,2));
    //beepLabel.setSize(Size(40,1));
    beepLabel.setText("Beep");
    beepLabel.onClick(std::bind(&TestForm::beep, this));

    changeColorLabel.initialize();
    changeColorLabel.setPosition(Size(1,3));
    changeColorLabel.setSize(Size(40,1));
    changeColorLabel.setText("Change Color");
    changeColorLabel.onClick(std::bind(&TestForm::changeColor, this));

    exitLabel.initialize();
    exitLabel.setPosition(Size(1,4));
    exitLabel.setSize(Size(40,1));
    exitLabel.setText("Exit");
    exitLabel.onClick(std::bind(&TestForm::quitGame, this));

    smileyFace.initialize();
    smileyFace.setPosition(Size(30,30));
    smileyFace.setSize(Size(40,1));
    smileyFace.setText(":)");
    add(&smileyFace);

    messageLabel.initialize();
    messageLabel.setPosition(Size(1,1));
    messageLabel.setSize(Size(getSize().x - 2,1));
    messageLabel.setText("Welcome to Cursen!");
    messageLabel.setForeground(Color::YELLOW);

    //checkBox = new CheckBox(Size(1,6));
    checkBox.initialize();
    checkBox.setPosition(Size(1,6));
    checkBox.setText("Exit Enabled");
    checkBox.setState(CheckState::INDETERMINATE);
    checkBox.onClick(std::bind(&TestForm::disable, this));

    checkBox2.initialize();
    checkBox2.setPosition(Size(1,7));
    checkBox2.setText("Rainbow Enabled");
    checkBox2.onClick(std::bind(&TestForm::doRainbow, this));

    twirlCheck.initialize();
    twirlCheck.setPosition(Size(1,8));
    twirlCheck.setText("Twirl Enabled");
    twirlCheck.onClick(std::bind(&TestForm::activateTwirl, this));

    twirlProgress.initialize();
    twirlProgress.setPosition(Size(20, 4));

    box.add(&twirlProgress);
    titleBox.addRelative(&messageLabel);
    box.addRelative(&flashLabel);
    box.addRelative(&beepLabel);
    box.addRelative(&changeColorLabel);
    box.addRelative(&exitLabel);
    box.addRelative(&checkBox);
    box.addRelative(&checkBox2);
    box.addRelative(&twirlCheck);

    pressMe.initialize();
    pressMe.setLength(21);
    pressMe.setText("");
    pressMe.setPosition(Size(2,13));
    //pressMe.setText("Hello");
    add(&pressMe);

    cursor.setStart(&flashLabel);
    cursor.mapComponent(&flashLabel, ArrowMap(nullptr, &pressMe, nullptr, &beepLabel));
    cursor.mapComponent(&beepLabel, ArrowMap(nullptr, &flashLabel, nullptr, &changeColorLabel));
    cursor.mapComponent(&changeColorLabel, ArrowMap(nullptr, &beepLabel, nullptr, &exitLabel));
    cursor.mapComponent(&exitLabel, ArrowMap(nullptr, &changeColorLabel, nullptr, &checkBox));
    cursor.mapComponent(&checkBox, ArrowMap(nullptr, &exitLabel, nullptr, &checkBox2));
    cursor.mapComponent(&checkBox2, ArrowMap(nullptr, &checkBox, nullptr, &twirlCheck));
    cursor.mapComponent(&twirlCheck, ArrowMap(nullptr, &checkBox2, nullptr, &pressMe));
    cursor.mapComponent(&pressMe, ArrowMap(nullptr, &twirlCheck, nullptr, &flashLabel));
    cursor.setEnabled(true);

    onKeyPress(std::bind(&TestForm::keyPress, this, std::placeholders::_1));
}

void TestForm::activateTwirl() {
    twirlProgress.toggle();
    twirlCheck.toggle();
}

void TestForm::keyPress(const Event &event) {
    if (event.key.code == 'q') {
        cursor.setEnabled(!cursor.isEnabled());
    }
    if (event.key.code == 'g') {
        if (!AlarmManager::HasActiveAlarm(&flashLabel))
            flashLabel.startGlow();
        else
            flashLabel.stopGlow();
    }
}

void TestForm::quitGame() {
    CursenApplication::Quit();
}

void TestForm::flash() {
    CursesManager::Flash();
    messageLabel.setText("Flashy Flash");
}

void TestForm::beep() {
    CursesManager::Beep();
    messageLabel.setText("Beep Boop");
}

void TestForm::changeColor() {
    static int i = 0;
    i++;
    i = i % 6;
    if (i == 0) {
        box.setForeground(Color::RED);
    }
    else if (i == 1) {
        box.setForeground(Color::ORANGE);
    }
    else if (i == 2) {
        box.setForeground(Color::YELLOW);
    }
    else if (i == 3) {
        box.setForeground(Color::GREEN);
    }
    else if (i == 4) {
        box.setForeground(Color::BLUE);
    }
    else if (i == 5) {
        box.setForeground(Color::VIOLET);
    }

}

void TestForm::moveComponent(const Event &event) {
    if (event.arrowPress.right) {
        box.move(Size(1, 0));
        changeColor();
    }
    if (event.arrowPress.left) {
        box.move(Size(-1, 0));
        changeColor();
    }
    if (!cursor.isEnabled()) {
        if (event.arrowPress.up) {
            box.move(Size(0, -1));
            changeColor();
        }
        if (event.arrowPress.down) {
            box.move(Size(0, 1));
            changeColor();
        }
    }
}

void TestForm::disable() {
    checkBox.toggle();
    exitLabel.setEnabled(checkBox.isChecked());
}

void TestForm::alarmFunction() {
    changeColor();
}

void TestForm::doRainbow() {
    static bool flashing = false;
    if (flashing) {
        AlarmManager::StopAlarm(this);
        box.setForeground(Color::WHITE);
    }
    else {
        AlarmManager::StartAlarm(this, std::bind(&TestForm::alarmFunction, this), .06);
    }
    flashing = !flashing;
    checkBox2.toggle();
}