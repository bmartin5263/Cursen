//
// Created by Brandon Martin on 4/10/19.
//

#include "UnoTitle.h"

UnoTitle::UnoTitle() {

}

UnoTitle::UnoTitle(const Size &pos) : TextComponent(pos) {

}

void UnoTitle::initialize() {
    TextComponent::initialize();
    setSize(Size(20, 3));
}

void UnoTitle::render() {
    Content* content = getContent();

    chtype line1[] =
            {'|','|',' ','|','|',' ','|','|','\\',' ','|','|',' ',' ','/','/',' ','\\','\\',' '};

    for (int i = 0; i < getSize().x; i++) {
        if (i < 5)
            line1[i] = line1[i] | Color::BLUE;
        else if (i < 12)
            line1[i] = line1[i] | Color::GREEN;
        else
            line1[i] = line1[i] | Color::RED;
    }

    chtype line2[] =
            {'|','|',' ','|','|',' ','|','|','\\','\\','|','|',' ','(','(',' ',' ',' ',')',')'};

    for (int i = 0; i < getSize().x; i++) {
        if (i < 5)
            line2[i] = line2[i] | Color::BLUE;
        else if (i < 12)
            line2[i] = line2[i] | Color::GREEN;
        else
            line2[i] = line2[i] | Color::RED;
    }

    chtype line3[] =
            {'\\','\\',' ','/','/',' ','|','|',' ','\\','|','|',' ',' ','\\','\\',' ','/','/',' '};

    for (int i = 0; i < getSize().x; i++) {
        if (i < 5)
            line3[i] = line3[i] | Color::BLUE;
        else if (i < 12)
            line3[i] = line3[i] | Color::GREEN;
        else
            line3[i] = line3[i] | Color::RED;
    }

    content->writeLine(line1, Size(0,0));
    content->writeLine(line2, Size(0,1));
    content->writeLine(line3, Size(0,2));
}

