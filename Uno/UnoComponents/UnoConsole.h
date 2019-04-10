//
// Created by Brandon Martin on 4/10/19.
//

#ifndef CURSEN_UNOCONSOLE_H
#define CURSEN_UNOCONSOLE_H


#include "Components/AggregateComponent.h"
#include "Components/Box.h"
#include "Components/Label.h"

class UnoConsole : public AggregateComponent {

public:

    UnoConsole();
    UnoConsole(const Size& pos);

    void initialize() override;

    void setText(const std::string &text) override;

    std::string getText() override;

private:

    Box uno_box;
    Box console_box;
    Label console_message;

};


#endif //CURSEN_UNOCONSOLE_H
