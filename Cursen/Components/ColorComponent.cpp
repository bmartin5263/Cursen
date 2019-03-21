//
// Created by Brandon Martin on 3/21/19.
//

#include "ColorComponent.h"
#include "CursenApplication.h"

ColorComponent::ColorComponent(const Vect2i &pos, const Vect2i &dim) : Component(pos, dim) {
    initialize();
}

void ColorComponent::initialize() {
    this->foreground = CursenApplication::GetColorPalette().getForeground();
    this->background = CursenApplication::GetColorPalette().getBackground();
    this->highlight_foreground = CursenApplication::GetColorPalette().getHighlight();
    this->highlight_background = CursenApplication::GetColorPalette().getBackground();
    this->disabled_foreground = CursenApplication::GetColorPalette().getDisabled();
    this->disabled_background = CursenApplication::GetColorPalette().getBackground();
    this->draw_color = ColorPair(this->foreground, this->background);
    this->onCursor(std::bind(&ColorComponent::cursorOn, this));
    this->offCursor(std::bind(&ColorComponent::cursorOff, this));
}

void ColorComponent::setForeground(const Color &color) {
    foreground = color;
    draw_color.fg = color;
    invalidate();
}

void ColorComponent::setForegroundAll(const Color &color) {
    setForeground(color);
    for (auto child : components) {
        child->setForegroundAll(color);
    }
}

Color ColorComponent::getForeground() {
    return foreground;
}

void ColorComponent::setBackground(const Color &color) {
    background = color;
    draw_color.bg = color;
    invalidate();
}

void ColorComponent::setBackgroundAll(const Color &color) {
    setBackground(color);
    for (auto child : components) {
        child->setBackgroundAll(color);
    }
}

Color ColorComponent::getBackground() {
    return background;
}

void ColorComponent::cursorOn() {
    draw_color.fg = highlight_foreground;
    draw_color.bg = highlight_background;
    invalidate();
}

void ColorComponent::cursorOff() {
    draw_color.fg = foreground;
    draw_color.bg = background;
    invalidate();
}

void ColorComponent::setEnabled(bool value) {
    Component::setEnabled(value);
    if (isEnabled()) {
        draw_color.fg = foreground;
        draw_color.bg = background;
    }
    else {
        draw_color.fg = disabled_foreground;
        draw_color.bg = disabled_background;
    }
    invalidate();
}
