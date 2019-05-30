//
// Created by Brandon Martin on 5/22/19.
//

#ifndef CURSEN_LOBBYGLOWBORDER_H
#define CURSEN_LOBBYGLOWBORDER_H


#include <Cursen/Drawing/Animation.h>
#include <Uno/Other/LobbyEffectGenerator.h>
#include "Cursen/Components/TextComponent.h"

class LobbyGlowBorder : public cursen::TextComponent
{
public:

    LobbyGlowBorder();

    void initialize() override;
    void render() override;

    void colorize() { colorFlag = true; };
    void blackAndWhite() { colorFlag = false; };

    void setEnabled(bool value) override;
    bool isEnabled() const override;

public:

    bool colorFlag;
    LobbyEffectGenerator generator;
    cursen::Animation animation;
    cursen::Content reference;

};


#endif //CURSEN_LOBBYGLOWBORDER_H
