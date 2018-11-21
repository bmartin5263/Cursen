//
// Created by Brandon Martin on 11/21/18.
//

#ifndef CURSEN_CANVAS_H
#define CURSEN_CANVAS_H

#include "SFML/Graphics.hpp"
#include "ncurses.h"
#include "panel.h"

/*
 * Class: Canvas
 *
 * Canvases are Window/Panel pairs that carry with them metadata about their size, initial color,
 * and location on the screen. They serve as a drawing board where elements can render their contents
 * onto and can be easily hidden when not in use.
 */
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
