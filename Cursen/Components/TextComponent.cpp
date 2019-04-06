//
// Created by Brandon Martin on 4/3/19.
//

#include <Events/AlarmManager.h>
#include "TextComponent.h"
#include "CursenApplication.h"

TextComponent::TextComponent() :
        Component(Size(0,0))
{
}

TextComponent::TextComponent(const Size &pos) :
        Component(pos)
{
}

TextComponent::TextComponent(const Size &pos, const Size &dim) :
        Component(pos), content(dim)
{
}

void TextComponent::initialize() {
    this->isHovered = false;
    this->foreground = CursenApplication::GetColorPalette().getForeground();
    this->background = CursenApplication::GetColorPalette().getBackground();
    this->highlight_foreground = CursenApplication::GetColorPalette().getHighlight();
    this->highlight_background = CursenApplication::GetColorPalette().getBackground();
    this->disabled_foreground = CursenApplication::GetColorPalette().getDisabled();
    this->disabled_background = CursenApplication::GetColorPalette().getBackground();
    this->draw_color = ColorPair(this->foreground, this->background);
    this->glow_frame = 5;
    this->onCursor(std::bind(&TextComponent::startGlow, this));
    this->offCursor(std::bind(&TextComponent::stopGlow, this));
}

void TextComponent::setForeground(const Color &color) {
    foreground = color;
    draw_color.fg = color;
    invalidate();
}

Color TextComponent::getForeground() {
    return foreground;
}

void TextComponent::setBackground(const Color &color) {
    background = color;
    draw_color.bg = color;
    invalidate();
}

Color TextComponent::getBackground() {
    return background;
}

void TextComponent::cursorOn() {
    isHovered = true;
    draw_color.fg = highlight_foreground;
    draw_color.bg = highlight_background;
    invalidate();
}

void TextComponent::cursorOff() {
    isHovered = false;
    draw_color.fg = foreground;
    draw_color.bg = background;
    invalidate();
}

void TextComponent::setEnabled(bool value) {
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

void TextComponent::setHighlight(const ColorPair &color) {
    highlight_background = color.bg;
    highlight_foreground = color.fg;
    if (isHovered) {
        draw_color.fg = color.fg;
        draw_color.bg = color.bg;
    }
    invalidate();
}

ColorPair TextComponent::getHighlight() {
    return ColorPair(highlight_foreground, highlight_background);
}

void TextComponent::setDisabled(const ColorPair &color) {
    disabled_background = color.bg;
    disabled_foreground = color.fg;
    invalidate();
}

ColorPair TextComponent::getDisabled() {
    return ColorPair(disabled_foreground, disabled_background);
}


Content * TextComponent::getContent() {
    return &content;
}

void TextComponent::setSize(const Size &size) {
    content.resize(size);
    invalidate();
}

Size TextComponent::getSize() {
    return content.getDimensions();
}

ColorPair& TextComponent::getCurrentDrawColor() {
    return draw_color;
}

void TextComponent::startGlow() {
    AlarmManager::StartAlarm(this, std::bind(&TextComponent::animateGlow, this), .07);
}

void TextComponent::stopGlow() {
    AlarmManager::StopAlarm(this);
    setForeground(Color::WHITE);
    glow_frame = 5;
}

void TextComponent::animateGlow() {
    if (glow_frame == 0) {
        setForeground(Color(231));
    }
    else if (glow_frame == 1) {
        setForeground(Color(230));
    }
    else if (glow_frame == 2) {
        setForeground(Color(229));
    }
    else if (glow_frame == 3) {
        setForeground(Color(228));
    }
    else if (glow_frame == 4) {
        setForeground(Color(227));
    }
    else if (glow_frame == 5) {
        setForeground(Color(226));
    }
    else if (glow_frame == 6) {
        setForeground(Color(226));
    }
    else if (glow_frame == 7) {
        setForeground(Color(226));
    }
    else if (glow_frame == 8) {
        setForeground(Color(226));
    }
    else if (glow_frame == 9) {
        setForeground(Color(226));
    }
    else if (glow_frame == 10) {
        setForeground(Color(227));
    }
    else if (glow_frame == 11) {
        setForeground(Color(228));
    }
    else if (glow_frame == 12) {
        setForeground(Color(229));
    }
    else if (glow_frame == 13) {
        setForeground(Color(230));
    }
    else if (glow_frame == 14) {
        setForeground(Color(231));
    }
    glow_frame = (glow_frame + 1) % 15;
}