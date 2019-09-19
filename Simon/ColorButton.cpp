//
// Created by Brandon Martin on 9/11/19.
//

#include <Uno/GameObjects/Player.h>
#include "ColorButton.h"

using namespace cursen;

void ColorButton::initialize()
{
    box.initialize();
    box.setSize(Vect2(10, 5));
    box.setPosition(Vect2(0, 0));
    addRelative(box);

    text.initialize();
    text.setSize(Vect2(8,1));
    text.setPosition(Vect2(1,2));
    text.setTextAlignment(TextAlignment::CENTER);
    addRelative(text);
}

void ColorButton::setText(const std::string& text)
{
    this->text.setText(text);
}

void ColorButton::flash()
{
    Color light;
    Color back;
    if (this->foreground == Color::BLUE)
    {
        light = Color(123);
        back = Color(17);
    }
    else if (this->foreground == Color::MAGENTA)
    {
        light = Color(213);
        back = Color(52);
    }
    else if (this->foreground == Color::GREEN)
    {
        light = Color(159);
        back = Color(22);
    }
    else
    {
        light = Color(253);
        back = Color(94);
    }
    AggregateComponent::setForeground(light);
    text.setBackground(back);
    box.setBackground(back);

    alarmHandle = AlarmManager::SetTimeout([this]() { unflash(); }, .2);
}

void ColorButton::unflash()
{
    AggregateComponent::setForeground(foreground);
    AggregateComponent::setBackground(Color::BLACK);
}

void ColorButton::setForeground(const Color& color)
{
    AggregateComponent::setForeground(color);
    this->foreground = color;
}
