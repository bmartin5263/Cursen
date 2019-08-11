//
// Created by Brandon Martin on 4/10/19.
//

#ifndef CURSEN_UNOCONSOLE_H
#define CURSEN_UNOCONSOLE_H


#include "Cursen/Components/AggregateComponent.h"
#include "Cursen/Components/Box.h"
#include "Cursen/Components/Label.h"
#include "UnoTitle.h"

class UnoConsole : public cursen::AggregateComponent {

public:

    UnoConsole();
    UnoConsole(const cursen::Vect2& pos);

    void initialize() override;

    void setText(const std::string &text) override;
    std::string getText() override;

    void setMessage(const std::string &text);
    void setWarning(const std::string &text);

private:

    cursen::Box uno_box;
    cursen::Box console_box;
    cursen::Label console_message;
    UnoTitle title;

};


#endif //CURSEN_UNOCONSOLE_H
