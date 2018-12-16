//
// Created by Brandon Martin on 12/4/18.
//

#include "BouncyBox.h"

std::vector<std::string> BouncyBox::colors {"red", "blue", "green", "yellow"};

BouncyBox::BouncyBox(int color) {
    vertical = 1;
    horizontal = 1;
    registerToCurrentScene(true, true);
}

void BouncyBox::draw() {
    TerminalManager::Draw(sprite);
}

void BouncyBox::update() {

}