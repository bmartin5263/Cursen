//
// Created by Brandon Martin on 6/30/19.
//

#ifndef CURSEN_DECKMETERCONTENT_H
#define CURSEN_DECKMETERCONTENT_H

#include "Cursen/Components/TextComponent.h"

class DeckMeterContent : public cursen::TextComponent
{

public:

    DeckMeterContent();
    DeckMeterContent(cursen::Vect2 pos);

    void initialize() override ;
    void render() override ;

    void setDeckSize(int size);
    void setCardCount(int count);

private:

    int max_len;
    int current_len;

};


#endif //CURSEN_DECKMETERCONTENT_H
