//
// Created by Brandon Martin on 8/26/19.
//

#include <Cursen/Drawing/CursesManager.h>
#include <Uno/Constants.h>
#include "IPEntryBox.h"

using namespace cursen;

void IPEntryBox::initialize()
{

    border.initialize();
    border.setSize(Vect2(48, 7));
    border.setPosition(Vect2(0,0));
    addRelative(border);

    title_border.initialize();
    title_border.setSize(Vect2(48, 3));
    title_border.setPosition(Vect2(0,0));
    title_border.setLowerLeft(CursesManager::LTEE);
    title_border.setLowerRight(CursesManager::RTEE);
    addRelative(title_border);

    window_label.initialize();
    window_label.setText("Host IP Address");
    window_label.setPosition(Vect2(17,1));
    window_label.setForeground(Color::YELLOW);
    addRelative(window_label);

    entry_border.initialize();
    entry_border.setSize(Vect2(48, 3));
    entry_border.setPosition(Vect2(0,2));
    entry_border.setFill(Content::TRANSPARENT);
    entry_border.setLowerRight(CursesManager::RTEE);
    entry_border.setUpperRight(CursesManager::RTEE);
    entry_border.setLowerLeft(CursesManager::LTEE);
    entry_border.setUpperLeft(CursesManager::LTEE);
    addRelative(entry_border);

//    ip_entry_label.initialize();
//    ip_entry_label.setText("Please Enter Host's IP Address");
//    ip_entry_label.setPosition(Vect2(9,4));
//    addRelative(ip_entry_label);

    entry_field.initialize();
    entry_field.setPosition(Vect2(1, 3));
    entry_field.setSize(Vect2(46, 1));
    entry_field.setEnabled(true);
    entry_field.setForeground(Color(84));
    entry_field.setPlaceholderText("e.g. 127.0.0.1");
    addRelative(entry_field);

    ipv4.initialize();
    ipv4.setPosition(Vect2(1, 5));
    ipv4.setText("IPv4");
    addRelative(ipv4);

    ipv6.initialize();
    ipv6.setPosition(Vect2(12, 5));
    ipv6.setText("IPv6");
    addRelative(ipv6);

    ipv8.initialize();
    ipv8.setPosition(Vect2(22, 5));
    ipv8.setText("Host Game?");
    ipv8.setHidden(true);
    addRelative(ipv8);

    entry_field.onKeyPress([this](EVENT_ARG) {
        entry_field.keyPress(event);
        checkField(entry_field.getText());
    });

    entry_field.onDeletePress([this](EVENT_ARG)
    {
        entry_field.deletePress(event);
        checkField(entry_field.getText());
    });
}

void IPEntryBox::checkField(const std::string& text)
{
    ipv4.uncheck();
    ipv6.uncheck();
    ipv8.uncheck();
    if (Constants::validateIPv6(text))
    {
        ipv6.check();
    }
    else if (Constants::validateIPv4(text))
    {
        ipv4.check();
    }
    else if (text == "Host's IP Address")
    {
        ipv8.setHidden(false);
        ipv8.check();
    }
    else
    {
        std::string lower = text;
        std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c) { return std::tolower(c); });
        if (lower == "localhost")
        {
            ipv6.check();
            ipv4.check();
        }
    }
}

void IPEntryBox::setHidden(bool value)
{
    AggregateComponent::setHidden(value);
    ipv8.setHidden(true);
    entry_field.setEnabled(!value);
    ipv4.uncheck();
    ipv6.uncheck();
}

std::string IPEntryBox::getText() const
{
    return entry_field.getText();
}

void IPEntryBox::setText(const std::string& text)
{
    entry_field.setText(text);
}
