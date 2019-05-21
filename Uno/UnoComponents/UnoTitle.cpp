//
// Created by Brandon Martin on 4/10/19.
//

#include "UnoTitle.h"

UnoTitle::UnoTitle() {

}

UnoTitle::UnoTitle(const cursen::Vect2 &pos) : TextComponent(pos) {

}

void UnoTitle::initialize() {
    TextComponent::initialize();
    setSize(cursen::Vect2(20, 3));
}

void UnoTitle::render() {
    cursen::Content& content = getContent();

    chtype line1[] =
            {'|','|',' ','|','|',' ','|','|','\\',' ','|','|',' ',' ','/','/',' ','\\','\\',' '};

    for (int i = 0; i < getSize().x; i++) {
        if (i < 5)
            line1[i] = line1[i] | cursen::Color::BLUE;
        else if (i < 12)
            line1[i] = line1[i] | cursen::Color::GREEN;
        else
            line1[i] = line1[i] | cursen::Color::RED;
    }

    chtype line2[] =
            {'|','|',' ','|','|',' ','|','|','\\','\\','|','|',' ','(','(',' ',' ',' ',')',')'};

    for (int i = 0; i < getSize().x; i++) {
        if (i < 5)
            line2[i] = line2[i] | cursen::Color::BLUE;
        else if (i < 12)
            line2[i] = line2[i] | cursen::Color::GREEN;
        else
            line2[i] = line2[i] | cursen::Color::RED;
    }

    chtype line3[] =
            {'\\','\\',' ','/','/',' ','|','|',' ','\\','|','|',' ',' ','\\','\\',' ','/','/',' '};

    for (int i = 0; i < getSize().x; i++) {
        if (i < 5)
            line3[i] = line3[i] | cursen::Color::BLUE;
        else if (i < 12)
            line3[i] = line3[i] | cursen::Color::GREEN;
        else
            line3[i] = line3[i] | cursen::Color::RED;
    }

    content.writeLine(line1, cursen::Vect2(0,0));
    content.writeLine(line2, cursen::Vect2(0,1));
    content.writeLine(line3, cursen::Vect2(0,2));

}

