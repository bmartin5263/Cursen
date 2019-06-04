//
// Created by Brandon Martin on 4/10/19.
//

#ifndef CURSEN_UNOTITLE_H
#define CURSEN_UNOTITLE_H

#include <Cursen/Components/StandardComponent.h>
#include "Cursen/Components/TextComponent.h"
#include "Cursen/Drawing/Animation.h"

class UnoTitle : public cursen::StandardComponent {

public:

    UnoTitle();
    UnoTitle(const cursen::Vect2& pos);

    void initialize() override;
    void render() override;

private:

    short blue_pair;
    short lit_blue_pair;
    short green_pair;
    short lit_green_pair;
    short red_pair;
    short lit_red_pair;

    cursen::Animation neonFlash;
    bool blueLit;
    bool redLit;
    bool greenLit;

};


#endif //CURSEN_UNOTITLE_H
