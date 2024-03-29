//
// Created by Brandon Martin on 5/21/19.
//

#include "StandardComponent.h"
#include "Cursen/CursenApplication.h"
#include "Cursen/Events/AlarmManager.h"
#include "Cursen/Drawing/TerminalManager.h"

namespace cursen
{

    StandardComponent::StandardComponent() :
            TextComponent(Vect2(0, 0)), animation(10), isHovered(false)
    {
    }

    StandardComponent::StandardComponent(const Vect2& pos) :
            TextComponent(pos), animation(10), isHovered(false)
    {
    }

    StandardComponent::StandardComponent(const Vect2& pos, const Vect2& dim) :
            TextComponent(pos, dim), animation(10), isHovered(false)
    {
    }

    void StandardComponent::initialize()
    {
        TextComponent::initialize();
        this->isHovered = false;
        this->foreground = CursenApplication::GetColorPalette().getForeground();
        this->background = CursenApplication::GetColorPalette().getBackground();
        this->highlight_foreground = CursenApplication::GetColorPalette().getHighlight();
        this->highlight_background = CursenApplication::GetColorPalette().getBackground();
        this->disabled_foreground = CursenApplication::GetColorPalette().getDisabled();
        this->disabled_background = CursenApplication::GetColorPalette().getBackground();
        this->draw_color = ColorPair(this->foreground, this->background);
        this->glow_frame = 8;
        this->onCursor([&]() { this->cursorOn(); });
        this->offCursor([&]() { this->cursorOff(); });

//        animation.setFrameDuration(.03);
//        animation.add([&]() { setForeground(Color::WHITE); }).setDuration(.1);
//        animation.add([&]() { setForeground(Color(195)); });
//        animation.add([&]() { setForeground(Color(154)); });
//        animation.add([&]() { setForeground(Color(118)); });
//        animation.add([&]() { setForeground(Color(82)); });
//        animation.add([&]() { setForeground(Color(Color::GREEN)); }).setDuration(.5);
//        animation.add([&]() { setForeground(Color(82)); });
//        animation.add([&]() { setForeground(Color(119)); });
//        animation.add([&]() { setForeground(Color(154)); });
//        animation.add([&]() { setForeground(Color(195)); });

        animation.setFrameDuration(.03);
        animation.add([&]() { setForeground(Color::WHITE); }).setDuration(.1);
        animation.add([&]() { setForeground(Color(195)); });
        animation.add([&]() { setForeground(Color(159)); });
        animation.add([&]() { setForeground(Color(123)); });
        animation.add([&]() { setForeground(Color(87)); });
        animation.add([&]() { setForeground(Color(51)); }).setDuration(.5);
        animation.add([&]() { setForeground(Color(87)); });
        animation.add([&]() { setForeground(Color(123)); });
        animation.add([&]() { setForeground(Color(159)); });
        animation.add([&]() { setForeground(Color(195)); });
//
//        animation.setFrameDuration(.03);
//        animation.add([&]() { setForeground(Color::WHITE); }).setDuration(.1);
//        animation.add([&]() { setForeground(Color(230)); });
//        animation.add([&]() { setForeground(Color(229)); });
//        animation.add([&]() { setForeground(Color(228)); });
//        animation.add([&]() { setForeground(Color(227)); });
//        animation.add([&]() { setForeground(Color(226)); }).setDuration(.5);
//        animation.add([&]() { setForeground(Color(227)); });
//        animation.add([&]() { setForeground(Color(228)); });
//        animation.add([&]() { setForeground(Color(229)); });
//        animation.add([&]() { setForeground(Color(230)); });
    }

    void StandardComponent::setForeground(const Color& color)
    {
        foreground = color;
        invalidate();
    }

    Color StandardComponent::getForeground() const
    {
        return foreground;
    }

    void StandardComponent::setBackground(const Color& color)
    {
        background = color;
        invalidate();
    }

    Color StandardComponent::getBackground() const
    {
        return background;
    }

    void StandardComponent::cursorOn()
    {
        isHovered = true;
        invalidate();
    }

    void StandardComponent::cursorOff()
    {
        isHovered = false;
        invalidate();
    }

    void StandardComponent::setEnabled(bool value)
    {
        Component::setEnabled(value);
        setCursable(value);
        invalidate();
    }

    void StandardComponent::setHighlight(const ColorPair& color)
    {
        highlight_background = color.bg;
        highlight_foreground = color.fg;
        if (isHovered)
        {
            draw_color.fg = color.fg;
            draw_color.bg = color.bg;
        }
        invalidate();
    }

    ColorPair StandardComponent::getHighlight() const
    {
        return ColorPair(highlight_foreground, highlight_background);
    }

    void StandardComponent::setDisabled(const ColorPair& color)
    {
        disabled_background = color.bg;
        disabled_foreground = color.fg;
        invalidate();
    }

    ColorPair StandardComponent::getDisabled() const
    {
        return ColorPair(disabled_foreground, disabled_background);
    }

    ColorPair& StandardComponent::getCurrentDrawColor()
    {
        return draw_color;
    }

    void StandardComponent::startGlow()
    {
        animation.start();
    }

    void StandardComponent::stopGlow()
    {
        animation.stop();
    }

    void StandardComponent::render()
    {
        if (isEnabled())
        {
            if (isHovered)
            {
                draw_color.fg = highlight_foreground;
                draw_color.bg = highlight_background;
            }
            else
            {
                draw_color.fg = foreground;
                draw_color.bg = background;
            }
        }
        else
        {
            draw_color.fg = disabled_foreground;
            draw_color.bg = disabled_background;
        }
    }

    StandardComponent::~StandardComponent()
    {
    }

}