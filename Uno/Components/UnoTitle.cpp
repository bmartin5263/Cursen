//
// Created by Brandon Martin on 4/10/19.
//

#include <Cursen/Drawing/CursesManager.h>
#include "UnoTitle.h"

UnoTitle::UnoTitle() {

}

UnoTitle::UnoTitle(const cursen::Vect2 &pos) : StandardComponent(pos) {

}

void UnoTitle::initialize() {
    StandardComponent::initialize();

    blueLit = false;
    redLit = false;
    greenLit = false;

    blue_pair = cursen::CursesManager::GetColorPair(cursen::ColorPair(cursen::Color::BLUE));
    green_pair = cursen::CursesManager::GetColorPair(cursen::ColorPair(cursen::Color::GREEN));
    red_pair = cursen::CursesManager::GetColorPair(cursen::ColorPair(cursen::Color::RED));
    lit_blue_pair = cursen::CursesManager::GetColorPair(cursen::ColorPair(159, cursen::Color(19)));
    lit_green_pair = cursen::CursesManager::GetColorPair(cursen::ColorPair(121, cursen::Color(28)));
    lit_red_pair = cursen::CursesManager::GetColorPair(cursen::ColorPair(219, cursen::Color(88)));

    neonFlash.setFrameDuration(4.0);
    neonFlash.add([&]() { blueLit = false; redLit = false; greenLit = false; invalidate(); });
    neonFlash.add([&]() { blueLit = true; invalidate(); }).setDuration(.4);
    neonFlash.add([&]() { blueLit = false; invalidate(); }).setDuration(.07);
    neonFlash.add([&]() { greenLit = true; invalidate(); }).setDuration(.4);
    neonFlash.add([&]() { greenLit = false; invalidate(); }).setDuration(.07);
    neonFlash.add([&]() { redLit = true; invalidate(); }).setDuration(.4);
    neonFlash.add([&]() { redLit = false; invalidate(); }).setDuration(.07);
    neonFlash.add([&]() { blueLit = true; redLit = true; greenLit = true; invalidate(); }).setDuration(.5);

    //neonFlash.start();

    setSize(cursen::Vect2(20, 3));
}

void UnoTitle::render() {
    cursen::Content& content = getContent();

    chtype line1[] =
            {'|','|',' ','|','|',' ','|','|','\\',' ','|','|',' ',' ','/','/',' ','\\','\\',' '};

    chtype line2[] =
            {'|','|',' ','|','|',' ','|','|','\\','\\','|','|',' ','(','(',' ',' ',' ',')',')'};

    chtype line3[] =
            {'\\','\\',' ','/','/',' ','|','|',' ','\\','|','|',' ',' ','\\','\\',' ','/','/',' '};

    int size = getSize().x;
    for (int i = 0; i < size; ++i)
    {
        if (i < 5)
        {
            if (blueLit)
            {
                if (line1[i] != ' ') line1[i] |= lit_blue_pair;
                if (line2[i] != ' ') line2[i] |= lit_blue_pair;
                if (line3[i] != ' ') line3[i] |= lit_blue_pair;
                line3[2] |= lit_blue_pair;
            }
            else
            {
                line1[i] |= blue_pair;
                line2[i] |= blue_pair;
                line3[i] |= blue_pair;
            }
        }
        else if (i < 12)
        {
            if (greenLit)
            {
                if (line1[i] != ' ') line1[i] |= lit_green_pair;
                if (line2[i] != ' ') line2[i] |= lit_green_pair;
                if (line3[i] != ' ') line3[i] |= lit_green_pair;
            }
            else
            {
                line1[i] |= green_pair;
                line2[i] |= green_pair;
                line3[i] |= green_pair;
            }
        }
        else
        {
            if (redLit)
            {
                if (line1[i] != ' ') line1[i] |= lit_red_pair;
                if (line2[i] != ' ') line2[i] |= lit_red_pair;
                if (line3[i] != ' ') line3[i] |= lit_red_pair;
                //line1[13] |= lit_red_pair;
                //line1[19] |= lit_red_pair;
                line1[16] |= lit_red_pair;
                //line3[13] |= lit_red_pair;
                //line3[19] |= lit_red_pair;
                line3[16] |= lit_red_pair;
            }
            else
            {
                line1[i] |= red_pair;
                line2[i] |= red_pair;
                line3[i] |= red_pair;
            }
        }
    }

    content.writeLine(line1, cursen::Vect2(0,0));
    content.writeLine(line2, cursen::Vect2(0,1));
    content.writeLine(line3, cursen::Vect2(0,2));

}

void UnoTitle::setEnabled(bool value)
{
    StandardComponent::setEnabled(value);
    if (value) neonFlash.start();
    else neonFlash.stop();
}

