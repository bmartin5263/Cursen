//
// Created by Brandon Martin on 9/11/19.
//

#ifndef CURSEN_COLORBUTTON_H
#define CURSEN_COLORBUTTON_H


#include <Cursen/Components/AggregateComponent.h>
#include <Cursen/Components/Box.h>
#include <Cursen/Components/Label.h>

class ColorButton : public cursen::AggregateComponent
{
public:

    void initialize() override;
    void setText(const std::string& text) override;
    void flash();
    void unflash();
    void setForeground(const cursen::Color& color) override;

private:

    cursen::Color foreground;
    cursen::Box box;
    cursen::Label text;
    cursen::AlarmHandle alarmHandle;

};


#endif //CURSEN_COLORBUTTON_H
