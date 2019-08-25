//
// Created by Brandon Martin on 4/10/19.
//

#include "UnoConsole.h"

UnoConsole::UnoConsole() :
    AggregateComponent(cursen::Vect2(0,0))
{

}

UnoConsole::UnoConsole(const cursen::Vect2 &pos) :
        AggregateComponent(pos)
{

}

void UnoConsole::initialize() {

    uno_box.initialize();
    uno_box.setPosition(cursen::Vect2(0,0));
    uno_box.setSize(cursen::Vect2(70,5));
    uno_box.setLowerLeft(ACS_LTEE);
    uno_box.setLowerRight(ACS_RTEE);
    add(uno_box);

    console_box.initialize();
    console_box.setPosition(cursen::Vect2(0,4));
    console_box.setSize(cursen::Vect2(70,3));
    console_box.setLowerLeft(ACS_LTEE);
    console_box.setLowerRight(ACS_RTEE);
    console_box.setUpperLeft(ACS_LTEE);
    console_box.setUpperRight(ACS_RTEE);
    add(console_box);

    console_message.initialize();
    console_message.setPosition(cursen::Vect2(1,5));
    console_message.setForeground(cursen::Color::YELLOW);
    add(console_message);

    title.initialize();
    title.setPosition(cursen::Vect2(25, 1));
    add(title);

}

void UnoConsole::setText(const std::string &text) {
    setMessage(text);
}

std::string UnoConsole::getText() {
    return console_message.getText();
}

void UnoConsole::setMessage(const std::string &text) {
    console_message.setForeground(cursen::Color::YELLOW);
    console_message.setText(text);
}

void UnoConsole::setWarning(const std::string &text) {
    console_message.setForeground(cursen::Color::MAGENTA);
    console_message.setText(text);
}

void UnoConsole::setForeground(const cursen::Color& color)
{
    console_message.setForeground(color);
}

void UnoConsole::setEnabled(bool value)
{
    title.setEnabled(value);
}

