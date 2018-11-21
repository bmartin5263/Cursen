//
// Created by Brandon Martin on 11/21/18.
//

#include "Canvas.h"

Canvas::Canvas(sf::Vector2i position, sf::Vector2i size) :
    window(nullptr), panel(nullptr), position(position), size(size)
{
    window = newwin(0,0,0,0);
    panel = new_panel(window);
}

Canvas::~Canvas() {
    del_panel(panel);
    delwin(window);
}