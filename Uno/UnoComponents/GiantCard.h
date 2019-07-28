//
// Created by Brandon Martin on 7/5/19.
//

#ifndef CURSEN_GIANTCARD_H
#define CURSEN_GIANTCARD_H


#include <Cursen/Components/AggregateComponent.h>
#include <Cursen/Components/Box.h>
#include <Cursen/Components/ASCIIArt.h>

class GiantCard : public cursen::AggregateComponent
{

public:

    GiantCard();
    GiantCard(const cursen::Vect2& pos);

    void initialize() override;
    void setSize(const cursen::Vect2& size);
    void injectCard(const Card& card);

    void setValuesFrom(GiantCard& giantCard);

    void shrink();
    void shrinkCompletely();
    void grow();

    void setNumberHidden(bool value);
    void setHidden(bool value) override;

    bool hasCardInjected();

private:

    cursen::Box border;
    cursen::ASCIIArt number;
    CardColor color;
    CardValues value;
    bool card_injected;

};


#endif //CURSEN_GIANTCARD_H
