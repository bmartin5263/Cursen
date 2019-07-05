//
// Created by Brandon Martin on 6/30/19.
//

#include "DeckMeterContent.h"

using namespace cursen;

DeckMeterContent::DeckMeterContent() :
    TextComponent(Vect2(0,0), Vect2(1,9)), max_len(0), current_len(0)
{

}

DeckMeterContent::DeckMeterContent(cursen::Vect2 pos) :
    TextComponent(pos, Vect2(1, 9)), max_len(0), current_len(0)
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

    chtype line[dimensions.y];
    for (int i = 0; i < dimensions.y; i++)
    {
        if (i < 3) line[i] = '=' | Color::GREEN;
        else if (i < 6) line[i] = '=' | Color::YELLOW;
        else line[i] = '=' | Color::RED;
    }

    content.writeColumn(line, 0);
}

void DeckMeterContent::setDeckSize(int size)
{
    max_len = size;
    invalidate();
}

void DeckMeterContent::setCardCount(int count)
{
    current_len = count;
}
