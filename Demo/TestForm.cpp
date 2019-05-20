//
// Created by Brandon Martin on 3/11/19.
//

#include "Drawing/CursesManager.h"
#include "CursenApplication.h"
#include "Events/AlarmManager.h"
#include "TestForm.h"

TestForm::TestForm() :
    Form(cursen::Vect2(70,33))
{

}

void TestForm::initialize() {
    setHidden(true);

    box.initialize();
    box.setPosition(cursen::Vect2(2,3));
    box.setSize(cursen::Vect2(21, 10));
    box.setHidden(false);

    titleBox.initialize();
    titleBox.setPosition(cursen::Vect2(0,0));
    titleBox.setSize(cursen::Vect2(getSize().x, 3));
    titleBox.setLowerRight(ACS_RTEE);
    titleBox.setLowerLeft(ACS_LTEE);
    titleBox.setDrawOrder(100);

    flashLabel.initialize();
    flashLabel.setPosition(cursen::Vect2(1,1));
    //flashLabel.setSize(cursen::Vect2(40,1));
    flashLabel.setText("Flash");
    flashLabel.onClick(std::bind(&TestForm::flash, this));

    beepLabel.initialize();
    beepLabel.setPosition(cursen::Vect2(1,2));
    //beepLabel.setSize(cursen::Vect2(40,1));
    beepLabel.setText("Beep");
    beepLabel.onClick(std::bind(&TestForm::beep, this));

    changeColorLabel.initialize();
    changeColorLabel.setPosition(cursen::Vect2(1,3));
    changeColorLabel.setSize(cursen::Vect2(40,1));
    changeColorLabel.setText("Change Color");
    changeColorLabel.onClick(std::bind(&TestForm::changeColor, this));

    exitLabel.initialize();
    exitLabel.setPosition(cursen::Vect2(1,4));
    exitLabel.setSize(cursen::Vect2(40,1));
    exitLabel.setText("Exit");
    exitLabel.onClick(std::bind(&TestForm::quitGame, this));

    smileyFace.initialize();
    smileyFace.setPosition(cursen::Vect2(30,30));
    smileyFace.setSize(cursen::Vect2(40,1));
    smileyFace.setText(":)");

    messageLabel.initialize();
    messageLabel.setPosition(cursen::Vect2(1,1));
    messageLabel.setSize(cursen::Vect2(getSize().x - 2,1));
    messageLabel.setText("Welcome to Cursen!");
    messageLabel.setForeground(cursen::Color::YELLOW);

    //checkBox = new CheckBox(cursen::Vect2(1,6));
    checkBox.initialize();
    checkBox.setPosition(cursen::Vect2(1,6));
    checkBox.setText("Exit Enabled");
    checkBox.setState(cursen::CheckState::INDETERMINATE);
    checkBox.onClick(std::bind(&TestForm::disable, this));

    checkBox2.initialize();
    checkBox2.setPosition(cursen::Vect2(1,7));
    checkBox2.setText("Rainbow Enabled");
    checkBox2.onClick(std::bind(&TestForm::doRainbow, this));

    twirlCheck.initialize();
    twirlCheck.setPosition(cursen::Vect2(1,8));
    twirlCheck.setText("Twirl Enabled");
    twirlCheck.onClick(std::bind(&TestForm::activateTwirl, this));

    twirlProgress.initialize();
    twirlProgress.setPosition(cursen::Vect2(20, 4));

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
    pressMe.setPosition(cursen::Vect2(2,13));
    //pressMe.setText("Hello");
    add(&pressMe);

    cursor.moveTo(&flashLabel);
    cursor.mapComponent(&flashLabel, cursen::ArrowMap(nullptr, &pressMe, nullptr, &beepLabel));
    cursor.mapComponent(&beepLabel, cursen::ArrowMap(nullptr, &flashLabel, nullptr, &changeColorLabel));
    cursor.mapComponent(&changeColorLabel, cursen::ArrowMap(nullptr, &beepLabel, nullptr, &exitLabel));
    cursor.mapComponent(&exitLabel, cursen::ArrowMap(nullptr, &changeColorLabel, nullptr, &checkBox));
    cursor.mapComponent(&checkBox, cursen::ArrowMap(nullptr, &exitLabel, nullptr, &checkBox2));
    cursor.mapComponent(&checkBox2, cursen::ArrowMap(nullptr, &checkBox, nullptr, &twirlCheck));
    cursor.mapComponent(&twirlCheck, cursen::ArrowMap(nullptr, &checkBox2, nullptr, &pressMe));
    cursor.mapComponent(&pressMe, cursen::ArrowMap(nullptr, &twirlCheck, nullptr, &flashLabel));
    cursor.setEnabled(true);

    onKeyPress(std::bind(&TestForm::keyPress, this, std::placeholders::_1));
}

void TestForm::activateTwirl() {
    twirlProgress.toggle();
    twirlCheck.toggle();
}

void TestForm::keyPress(const cursen::Event &event) {
    if (event.key.code == 'q') {
        cursor.setEnabled(!cursor.isEnabled());
    }
    if (event.key.code == 'g') {
        if (!cursen::AlarmManager::HasActiveAlarm(&flashLabel))
            flashLabel.startGlow();
        else
            flashLabel.stopGlow();
    }
}

void TestForm::quitGame() {
    cursen::CursenApplication::Quit();
}

void TestForm::flash() {
    cursen::CursesManager::Flash();
    messageLabel.setText("Flashy Flash");
}

void TestForm::beep() {
    cursen::CursesManager::Beep();
    messageLabel.setText("Beep Boop");
}

void TestForm::changeColor() {
    static int i = 0;
    i++;
    i = i % 6;
    if (i == 0) {
        box.setForeground(cursen::Color::RED);
    }
    else if (i == 1) {
        box.setForeground(cursen::Color::ORANGE);
    }
    else if (i == 2) {
        box.setForeground(cursen::Color::YELLOW);
    }
    else if (i == 3) {
        box.setForeground(cursen::Color::GREEN);
    }
    else if (i == 4) {
        box.setForeground(cursen::Color::BLUE);
    }
    else if (i == 5) {
        box.setForeground(cursen::Color::VIOLET);
    }

}

void TestForm::moveComponent(const cursen::Event &event) {
    if (event.arrowPress.right) {
        box.move(cursen::Vect2(1, 0));
        changeColor();
    }
    if (event.arrowPress.left) {
        box.move(cursen::Vect2(-1, 0));
        changeColor();
    }
    if (!cursor.isEnabled()) {
        if (event.arrowPress.up) {
            box.move(cursen::Vect2(0, -1));
            changeColor();
        }
        if (event.arrowPress.down) {
            box.move(cursen::Vect2(0, 1));
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
        cursen::AlarmManager::StopAlarm(this);
        box.setForeground(cursen::Color::WHITE);
    }
    else {
        cursen::AlarmManager::StartAlarm(this, std::bind(&TestForm::alarmFunction, this), .06);
    }
    flashing = !flashing;
    checkBox2.toggle();
}