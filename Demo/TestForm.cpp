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
    box = new Box(Vect2i(0,0), Vect2i(20,8));
    label1 = new Label(Vect2i(1,1), Vect2i(40,1));
    label2 = new Label(Vect2i(1,2), Vect2i(40,1));
    label3 = new Label(Vect2i(1,3), Vect2i(40,1));
    label4 = new Label(Vect2i(1,4), Vect2i(40,1));
    label5 = new Label(Vect2i(10,10), Vect2i(40,1));
    checkBox = new CheckBox(Vect2i(1,6));

    label1->setText("Flash");
    label2->setText("Beep");
    label3->setText("Change Color");
    label4->setText("Exit");
    label5->setText(":)");
    checkBox->setText("Disable Exit");

    label4->onClick(std::bind(&TestForm::quitGame, this));
    label3->onClick(std::bind(&TestForm::changeColor, this));
    label2->onClick(std::bind(&TestForm::beep, this));
    label1->onClick(std::bind(&TestForm::flash, this));
    checkBox->onClick(std::bind(&TestForm::disable, this));
    box->onArrowPress(std::bind(&TestForm::moveComponent, this, std::placeholders::_1));

    add(box);
    add(label5);
    box->add(label1);
    box->add(label2);
    box->add(label3);
    box->add(label4);
    box->add(checkBox);

    cursor = new Cursor(label1);
    cursor->mapComponent(label1, ArrowMap(nullptr, checkBox, nullptr, label2));
    cursor->mapComponent(label2, ArrowMap(nullptr, label1, nullptr, label3));
    cursor->mapComponent(label3, ArrowMap(nullptr, label2, nullptr, label4));
    cursor->mapComponent(label4, ArrowMap(nullptr, label3, nullptr, checkBox));
    cursor->mapComponent(checkBox, ArrowMap(nullptr, label4, nullptr, label1));
    cursor->setEnabled(true);

    onKeyPress(std::bind(&TestForm::keyPress, this, std::placeholders::_1));
}

void TestForm::keyPress(const Event &event) {
    if (event.key.code == 'q') {
        cursor->setEnabled(!cursor->isEnabled());
    }
}

void TestForm::enterPress(const Event &event) {
    label1->setText("A very long string");
}

void TestForm::arrowPress(const Event &event) {
    label1->setForeground(Color::GRAY);
}

void TestForm::quitGame() {
    CursenApplication::Quit();
}

void TestForm::flash() {
    CursesManager::Flash();
}

void TestForm::beep() {
    CursesManager::Beep();
}

void TestForm::changeColor() {
    static int i = 0;
    i++;
    i = i % 6;
    if (i == 0) {
        box->setForeground(Color::RED);
    }
    else if (i == 1) {
        box->setForeground(Color::ORANGE);
    }
    else if (i == 2) {
        box->setForeground(Color::YELLOW);
    }
    else if (i == 3) {
        box->setForeground(Color::GREEN);
    } else if (i == 4) {
        box->setForeground(Color::BLUE);
    }
    else if (i == 5) {
        box->setForeground(Color::VIOLET);
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
    label4->setEnabled(checkBox->isChecked());
    checkBox->switchState();
}

void TestForm::render() {
    content.clear();
}


