//
// Created by Brandon Martin on 12/4/18.
//

#include "BouncyBox.h"

std::vector<std::string> BouncyBox::colors {"red", "blue", "green", "yellow"};

BouncyBox::BouncyBox(int color) {
    vertical = 1;
    horizontal = 1;
    this->color = rand() % 4;
    int y = rand() % (TerminalManager::GetRows()-3);
    int x = rand() % (TerminalManager::GetColumns()-(int)strlen("X--------X"));
    boundingBox = sf::IntRect(x, y, (int)strlen("X--------X"), 3);
    registerToCurrentScene(true, true);

    dirty = true;

    body[0] = 'X';
    body[1] = '\0';
}

void BouncyBox::draw() {
    //TerminalManager::Draw(sprite);
    attron(UITools::GetColor(colors[color]).colorPair);
    mvaddstr(boundingBox.top, boundingBox.left,   "X--------X");
    mvaddstr(boundingBox.top+1, boundingBox.left, "|        |");
    mvaddstr(boundingBox.top+2, boundingBox.left, "X--------X");
    attron(UITools::GetColor(colors[color]).colorPair);
}

void BouncyBox::move(sf::Vector2i dir) {
    boundingBox.top += dir.y;
    boundingBox.left += dir.x;
}

void BouncyBox::update() {
    if (true) {
        sf::IntRect originalPos = boundingBox;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            move(sf::Vector2i(2, 0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            move(sf::Vector2i(-2, 0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            move(sf::Vector2i(0, -1));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            move(sf::Vector2i(0, 1));
        }
        if (UITools::IsHorizontallyOffscreen(boundingBox)) {
            boundingBox = originalPos;
        }
        if (UITools::IsVerticallyOffscreen(boundingBox)) {
            boundingBox = originalPos;
        }
        color = (color + 1) % 4;
    }
}