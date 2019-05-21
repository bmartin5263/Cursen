//
// Created by Brandon Martin on 5/21/19.
//

#include "StandardComponent.h"
#include "Cursen/CursenApplication.h"
#include "Cursen/Events/AlarmManager.h"
#include "Cursen/Drawing/CursesManager.h"

namespace cursen {

    StandardComponent::StandardComponent() :
            TextComponent(Vect2(0, 0)) {
        CursesManager::Register(this);
    }

    StandardComponent::StandardComponent(const Vect2 &pos) :
            TextComponent(pos) {
        CursesManager::Register(this);
    }

    StandardComponent::StandardComponent(const Vect2 &pos, const Vect2 &dim) :
            TextComponent(pos, dim) {
        CursesManager::Register(this);
    }

    void StandardComponent::initialize() {
        this->isHovered = false;
        this->foreground = CursenApplication::GetColorPalette().getForeground();
        this->background = CursenApplication::GetColorPalette().getBackground();
        this->highlight_foreground = CursenApplication::GetColorPalette().getHighlight();
        this->highlight_background = CursenApplication::GetColorPalette().getBackground();
        this->disabled_foreground = CursenApplication::GetColorPalette().getDisabled();
        this->disabled_background = CursenApplication::GetColorPalette().getBackground();
        this->draw_color = ColorPair(this->foreground, this->background);
        this->glow_frame = 8;
        this->onCursor(std::bind(&StandardComponent::cursorOn, this));
        this->offCursor(std::bind(&StandardComponent::cursorOff, this));
    }

    void StandardComponent::setDrawOrder(int order) {
        CursesManager::SetDrawOrder(this, order);
        Component::setDrawOrder(order);
    }

    void StandardComponent::setForeground(const Color &color) {
        foreground = color;
        invalidate();
    }

    Color StandardComponent::getForeground() {
        return foreground;
    }

    void StandardComponent::setBackground(const Color &color) {
        background = color;
        invalidate();
    }

    Color StandardComponent::getBackground() {
        return background;
    }

    void StandardComponent::cursorOn() {
        isHovered = true;
        invalidate();
    }

    void StandardComponent::cursorOff() {
        isHovered = false;
        invalidate();
    }

    void StandardComponent::setEnabled(bool value) {
        Component::setEnabled(value);
        setCursable(value);
        invalidate();
    }

    void StandardComponent::setHighlight(const ColorPair &color) {
        highlight_background = color.bg;
        highlight_foreground = color.fg;
        if (isHovered) {
            draw_color.fg = color.fg;
            draw_color.bg = color.bg;
        }
        invalidate();
    }

    ColorPair StandardComponent::getHighlight() {
        return ColorPair(highlight_foreground, highlight_background);
    }

    void StandardComponent::setDisabled(const ColorPair &color) {
        disabled_background = color.bg;
        disabled_foreground = color.fg;
        invalidate();
    }

    ColorPair StandardComponent::getDisabled() {
        return ColorPair(disabled_foreground, disabled_background);
    }

    ColorPair &StandardComponent::getCurrentDrawColor() {
        return draw_color;
    }

    void StandardComponent::startGlow() {
        AlarmManager::StartAlarm(this, std::bind(&StandardComponent::animateGlow, this), .03);
    }

    void StandardComponent::stopGlow() {
        AlarmManager::StopAlarm(this);
        setForeground(Color::WHITE);
        glow_frame = 8;
    }

    void StandardComponent::animateGlow() {
        if (glow_frame == 0) {
            setForeground(Color(195));
        } else if (glow_frame == 1) {
            setForeground(Color(195));
        } else if (glow_frame == 2) {
            setForeground(Color(159));
        } else if (glow_frame == 3) {
            setForeground(Color(159));
        } else if (glow_frame == 4) {
            setForeground(Color(123));
        } else if (glow_frame == 5) {
            setForeground(Color(123));
        } else if (glow_frame == 6) {
            setForeground(Color(87));
        } else if (glow_frame == 7) {
            setForeground(Color(87));
        } else if (glow_frame == 8) {
            setForeground(Color(51));
        } else if (glow_frame == 9) {
            setForeground(Color(51));
        } else if (glow_frame == 10) {
            setForeground(Color(51));
        } else if (glow_frame == 11) {
            setForeground(Color(51));
        } else if (glow_frame == 12) {
            setForeground(Color(51));
        } else if (glow_frame == 13) {
            setForeground(Color(51));
        } else if (glow_frame == 14) {
            setForeground(Color(51));
        } else if (glow_frame == 15) {
            setForeground(Color(87));
        } else if (glow_frame == 16) {
            setForeground(Color(87));
        } else if (glow_frame == 17) {
            setForeground(Color(123));
        } else if (glow_frame == 18) {
            setForeground(Color(123));
        } else if (glow_frame == 19) {
            setForeground(Color(159));
        } else if (glow_frame == 20) {
            setForeground(Color(159));
        } else if (glow_frame == 21) {
            setForeground(Color(195));
        } else if (glow_frame == 22) {
            setForeground(Color(195));
        }
        else if (glow_frame == 23) {
            setForeground(Color(195));
        }
        else if (glow_frame == 24) {
            setForeground(Color(195));
        }
        else if (glow_frame == 25) {
            setForeground(Color(195));
        }
        else if (glow_frame == 26) {
            setForeground(Color(195));
        }
        else if (glow_frame == 27) {
            setForeground(Color(195));
        }
        else if (glow_frame == 28) {
            setForeground(Color(195));
        }
        glow_frame = (glow_frame + 1) % 29;
    }

    void StandardComponent::render() {
        if (isEnabled()) {
            if (isHovered) {
                draw_color.fg = highlight_foreground;
                draw_color.bg = highlight_background;
            } else {
                draw_color.fg = foreground;
                draw_color.bg = background;
            }
        } else {
            draw_color.fg = disabled_foreground;
            draw_color.bg = disabled_background;
        }
    }

    StandardComponent::~StandardComponent()
    {
        CursesManager::Deregister(this);
    }

}