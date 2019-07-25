//
// Created by Brandon Martin on 7/4/19.
//

#include "HandCard.h"

using namespace cursen;

HandCard::HandCard() :
    AggregateComponent(), hovered(false), wild(false)
{

}

HandCard::HandCard(cursen::Vect2 pos) :
    AggregateComponent(pos), hovered(false), wild(false)
{

}

void HandCard::initialize()
{
    border.initialize();
    border.setPosition(Vect2(0,0));
    border.setSize(Vect2(4,4));
    addRelative(&border);

    upperLabel.initialize();
    upperLabel.setPosition(Vect2(1,1));
    upperLabel.setDrawOrder(border.getDrawOrder() + 1);
    upperLabel.setText(" ?");
    addRelative(&upperLabel);

    lowerLabel.initialize();
    lowerLabel.setPosition(Vect2(1,2));
    lowerLabel.setDrawOrder(border.getDrawOrder() + 1);
    lowerLabel.setText("? ");
    addRelative(&lowerLabel);

    onCursor([&]() { this->hoverOn(); });
    offCursor([&]() { this->hoverOff(); });

    this->color = Color::WHITE;

    animation.setFrameDuration(.06f);
    animation.add([&]() { setForeground(cursen::Color::RED); });
    animation.add([&]() { setForeground(cursen::Color::ORANGE); });
    animation.add([&]() { setForeground(cursen::Color::YELLOW); });
    animation.add([&]() { setForeground(cursen::Color::GREEN); });
    animation.add([&]() { setForeground(cursen::Color::BLUE); });
    animation.add([&]() { setForeground(cursen::Color::LAVENDER); });
}

void HandCard::setLeft()
{
    lowerLabel.setText("<-");
    upperLabel.setText("<-");
    lowerLabel.setForeground(Color::WHITE);
    upperLabel.setForeground(Color::WHITE);
    border.setForeground(Color::WHITE);
}

void HandCard::setRight()
{
    lowerLabel.setText("->");
    upperLabel.setText("->");
    lowerLabel.setForeground(Color::WHITE);
    upperLabel.setForeground(Color::WHITE);
    border.setForeground(Color::WHITE);
}

void HandCard::hoverOn()
{
    if (!hovered)
    {
        move(Vect2(0, -1));
        hovered = true;
    }
}

void HandCard::hoverOff()
{
    if (hovered)
    {
        move(Vect2(0, 1));
        if (wild) animation.start();
        else setForeground(this->color);
        hovered = false;
    }
}

void HandCard::injectCard(const Card& card)
{
    if (card.isWild())
    {
        this->color = Color::WHITE;
        wild = true;
    }
    else
    {
        this->color = Card::ConvertToColor(card.getColor());
        wild = false;
        if (!hovered)
        {
            setForeground(this->color);
        }
    }
    lowerLabel.setText(Card::getLowerLabel(card.getValue()));
    upperLabel.setText(Card::getUpperLabel(card.getValue()));
    if (!hovered)
    {
        if (wild) animation.start();
        else setForeground(this->color);
    }
}

void HandCard::setHidden(bool value)
{
    AggregateComponent::setHidden(value);
    setCursable(!value);
}

void HandCard::setForeground(const cursen::Color& color)
{
    border.setForeground(color);
    lowerLabel.setForeground(Color::WHITE);
    upperLabel.setForeground(Color::WHITE);
}

