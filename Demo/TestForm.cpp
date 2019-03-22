//
// Created by Brandon Martin on 3/11/19.
//

#include <Drawing/CursesManager.h>
#include <CursenApplication.h>
#include "Cursor/Cursor.h"
#include "Components/Label.h"
#include "TestForm.h"
#include "Components/CheckBox.h"

TestForm::TestForm() :
    Form(Vect2i(70,33))
{

}

void TestForm::initialize() {
    setHidden(true);

    box = new Box(Vect2i(3,3), Vect2i(20,8));
    box->enableDebugging();
    box->onArrowPress(std::bind(&TestForm::moveComponent, this, std::placeholders::_1));

    titleBox = new Box(Vect2i(0,0), Vect2i(getDimensions().x, 3));
    titleBox->setLowerRight(ACS_RTEE);
    titleBox->setLowerLeft(ACS_LTEE);

    flashLabel = new Label(Vect2i(1,1), Vect2i(40,1));
    flashLabel->setText("Flash");
    flashLabel->onClick(std::bind(&TestForm::flash, this));

    beepLabel = new Label(Vect2i(1,2), Vect2i(40,1));
    beepLabel->setText("Beep");
    beepLabel->onClick(std::bind(&TestForm::beep, this));

    changeColorLabel = new Label(Vect2i(1,3), Vect2i(40,1));
    changeColorLabel->setText("Change Color");
    changeColorLabel->onClick(std::bind(&TestForm::changeColor, this));

    exitLabel = new Label(Vect2i(1,4), Vect2i(40,1));
    exitLabel->setText("Exit");
    exitLabel->onClick(std::bind(&TestForm::quitGame, this));

    smileyFace = new Label(Vect2i(30,30), Vect2i(40,1));
    smileyFace->setText(":)");

    messageLabel = new Label(Vect2i(1,1), Vect2i(getDimensions().x - 2,1));
    messageLabel->setText("Welcome to Cursen!");
    messageLabel->setForeground(Color::YELLOW);

    checkBox = new CheckBox(Vect2i(1,6));
    checkBox->setText("Disable Exit");
    checkBox->onClick(std::bind(&TestForm::disable, this));


    add(titleBox);
    add(box);
    add(smileyFace);
    titleBox->addRelative(messageLabel);
    box->addRelative(flashLabel);
    box->addRelative(beepLabel);
    box->addRelative(changeColorLabel);
    box->addRelative(exitLabel);
    box->addRelative(checkBox);

    cursor = new Cursor(flashLabel);
    cursor->mapComponent(flashLabel, ArrowMap(nullptr, checkBox, nullptr, beepLabel));
    cursor->mapComponent(beepLabel, ArrowMap(nullptr, flashLabel, nullptr, changeColorLabel));
    cursor->mapComponent(changeColorLabel, ArrowMap(nullptr, beepLabel, nullptr, exitLabel));
    cursor->mapComponent(exitLabel, ArrowMap(nullptr, changeColorLabel, nullptr, checkBox));
    cursor->mapComponent(checkBox, ArrowMap(nullptr, exitLabel, nullptr, flashLabel));
    cursor->setEnabled(true);

    onKeyPress(std::bind(&TestForm::keyPress, this, std::placeholders::_1));
}

void TestForm::keyPress(const Event &event) {
    if (event.key.code == 'q') {
        cursor->setEnabled(!cursor->isEnabled());
    }
}

void TestForm::enterPress(const Event &event) {
    flashLabel->setText("A very long string");
}

void TestForm::arrowPress(const Event &event) {
    flashLabel->setForeground(Color::GRAY);
}

void TestForm::quitGame() {
    CursenApplication::Quit();
}

void TestForm::flash() {
    CursesManager::Flash();
    messageLabel->setText("Flashy Flash");
}

void TestForm::beep() {
    CursesManager::Beep();
    messageLabel->setText("Beep Boop");
}

void TestForm::changeColor() {
    static int i = 0;
    i++;
    i = i % 6;
    if (i == 0) {
        box->setForeground(Color::RED);
        messageLabel->setText("Red");
    }
    else if (i == 1) {
        box->setForeground(Color::ORANGE);
        messageLabel->setText("Orange");
    }
    else if (i == 2) {
        box->setForeground(Color::YELLOW);
        messageLabel->setText("Yellow");
    }
    else if (i == 3) {
        box->setForeground(Color::GREEN);
        messageLabel->setText("Green");
    } else if (i == 4) {
        box->setForeground(Color::BLUE);
        messageLabel->setText("Blue");
    }
    else if (i == 5) {
        box->setForeground(Color::VIOLET);
        messageLabel->setText("Violet");
    }

}

void TestForm::moveComponent(const Event &event) {
    if (event.arrowPress.right) {
        box->move(Vect2i(1, 0));
        changeColor();
    }
    if (event.arrowPress.left) {
        box->move(Vect2i(-1, 0));
        changeColor();
    }
    if (!cursor->isEnabled()) {
        if (event.arrowPress.up) {
            box->move(Vect2i(0, -1));
            changeColor();
        }
        if (event.arrowPress.down) {
            box->move(Vect2i(0, 1));
            changeColor();
        }
    }
}

void TestForm::disable() {
    exitLabel->setEnabled(checkBox->isChecked());
    checkBox->switchState();
}

void TestForm::render() {
    content.clear();
}


