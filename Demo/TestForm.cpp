//
// Created by Brandon Martin on 3/11/19.
//

#include <Drawing/CursesManager.h>
#include <CursenApplication.h>
#include "Cursor/Cursor.h"
#include "Components/Label.h"
#include "TestForm.h"

void TestForm::initialize() {
    label1 = new Label(Vect2d(1,1), Vect2d(40,1));
    label2 = new Label(Vect2d(1,2), Vect2d(40,1));
    label3 = new Label(Vect2d(1,3), Vect2d(40,1));
    label4 = new Label(Vect2d(1,4), Vect2d(40,1));

    label1->setText("1. New Game");
    label2->setText("2. Load Game");
    label3->setText("3. Settings");
    label4->setText("4. Exit");

    label4->onClick(std::bind(&TestForm::quitGame, this));

    addComponent(label1);
    addComponent(label2);
    addComponent(label3);
    addComponent(label4);

    cursor = new Cursor(label1);
    cursor->addComponent(label1, ArrowMap(nullptr, label4, nullptr, label2));
    cursor->addComponent(label2, ArrowMap(nullptr, label1, nullptr, label3));
    cursor->addComponent(label3, ArrowMap(nullptr, label2, nullptr, label4));
    cursor->addComponent(label4, ArrowMap(nullptr, label3, nullptr, label1));
    cursor->setEnabled(true);
}

void TestForm::destroy() {
    delete label1;
}

void TestForm::keyPress(const Event &event) {
    if (event.key.code == '1') {
        label1->setColor(Color::PURPLE);
    }
    if (event.key.code == '2') {
        label1->setColor(Color(21));
    }
    if (event.key.code == '3') {
        label1->setColor(Color(63));
    }
    if (event.key.code == '4') {
        label1->setColor(Color(93));
    }
    if (event.key.code == '5') {
        label1->setColor(Color::GetRandomColor());
    }
    if (event.key.code == '6') {
        label1->setColor(Color::GetRandomColor());
    }
}

void TestForm::enterPress(const Event &event) {
    label1->setText("A very long string");
}

void TestForm::arrowPress(const Event &event) {
    label1->setColor(Color::GRAY);
}

void TestForm::quitGame() {
    CursenApplication::Quit();
}



