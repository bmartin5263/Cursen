//
// Created by Brandon Martin on 6/30/19.
//

#include <cmath>
#include "DeckMeterContent.h"

using namespace cursen;

DeckMeterContent::DeckMeterContent() :
    TextComponent(Vect2(0,0), Vect2(1,9)), tick_val(0), current_len(0)
{

}

DeckMeterContent::DeckMeterContent(cursen::Vect2 pos) :
    TextComponent(pos, Vect2(1, 9)), tick_val(0), current_len(0)
{

}

void DeckMeterContent::initialize()
{
    TextComponent::initialize();
}

void DeckMeterContent::render()
{
    Content& content = getContent();
    Vect2 dimensions = getSize();

    size_t num_equals = (size_t)ceil((double)current_len / tick_val);

    chtype line[dimensions.y];
//
//    short red_pair = Color::RED.getColorPair();
//    short green_pair = Color::GREEN.getColorPair();
//    short yellow_pair = Color::YELLOW.getColorPair();

    int index = 8;
    for (int i = 0; i < num_equals; ++i)
    {
        if (index > 5) line[index] = '=' | Color::MAGENTA;
        else if (index > 2) line[index] = '=' | Color::YELLOW;
        else line[index] = '=' | Color::GREEN;
        index--;
    }
    for (; index >= 0; --index)
    {
        line[index] = ' ';
    }

    content.writeColumn(line, 0);
}

void DeckMeterContent::setDeckSize(size_t size)
{
    tick_val = size / 9;
    invalidate();
}

void DeckMeterContent::setCardCount(size_t count)
{
    current_len = count;
    invalidate();
}
