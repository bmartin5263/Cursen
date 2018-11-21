//
// Created by Brandon Martin on 11/21/18.
//

#ifndef CURSEN_CANVAS_H
#define CURSEN_CANVAS_H

#include "SFML/Graphics.hpp"
#include "ncurses.h"
#include "panel.h"

class Canvas {

public:

    Canvas(sf::Vector2i position, sf::Vector2i size);
    Canvas(const Canvas &other) = delete;
    Canvas& operator = (const Canvas & other) = delete;
    ~Canvas();

    WINDOW* getWindow() const { return window; };

private:

    WINDOW* window;
    PANEL* panel;
    sf::Vector2i position;
    sf::Vector2i size;
};


#endif //CURSEN_CANVAS_H
