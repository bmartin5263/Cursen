//
// Created by Brandon Martin on 12/4/18.
//

#include "BouncyBox.h"

std::vector<std::string> BouncyBox::colors {"red", "blue", "green", "yellow"};

BouncyBox::BouncyBox() {
    vertical = 1;
    horizontal = 1;
    color = rand() % 4;
    registerToCurrentScene(true, true);
    int y = rand() % (TerminalManager::GetRows()-3);
    int x = rand() % (TerminalManager::GetColumns()-(int)strlen("XXXXXXX"));
    boundingBox = sf::IntRect(x, y, (int)strlen("XXXXXXX"), 3);
}

void BouncyBox::draw() {
    attron(UITools::GetColor(colors[color]).colorPair);
    mvaddstr(boundingBox.top, boundingBox.left,   "XXXXXXX");
    mvaddstr(boundingBox.top+1, boundingBox.left, "X     X");
    mvaddstr(boundingBox.top+2, boundingBox.left, "XXXXXXX");
    attroff(UITools::GetColor(colors[color]).colorPair);
}

void BouncyBox::update() {
    //color = (color + 1) % 4;
    sf::IntRect originalPos = boundingBox;
    move(sf::Vector2i(horizontal, vertical));
    if (UITools::IsHorizontallyOffscreen(boundingBox)) {
        horizontal = -horizontal;
        boundingBox = originalPos;
        move(sf::Vector2i(horizontal, vertical));
    }
    if (UITools::IsVerticallyOffscreen(boundingBox)) {
        vertical = -vertical;
        boundingBox = originalPos;
        move(sf::Vector2i(horizontal, vertical));
    }
}