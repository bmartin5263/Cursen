//
// Created by Brandon Martin on 8/26/19.
//

#ifndef CURSEN_IPENTRYBOX_H
#define CURSEN_IPENTRYBOX_H


#include <Cursen/Components/AggregateComponent.h>
#include <Cursen/Components/Box.h>
#include <Cursen/Components/Label.h>
#include <Cursen/Components/TextField.h>
#include <Cursen/Components/CheckBox.h>

class IPEntryBox : public cursen::AggregateComponent
{
public:

    void initialize() override;
    void checkField(const std::string& text);
    void setHidden(bool value) override;
    std::string getText() override;
    void setText(const std::string& text) override;

private:

    cursen::Box border;
    cursen::Box title_border;
    cursen::Box entry_border;
    cursen::Label ip_entry_label;
    cursen::Label window_label;
    cursen::TextField entry_field;
    cursen::CheckBox ipv4;
    cursen::CheckBox ipv6;

};


#endif //CURSEN_IPENTRYBOX_H
