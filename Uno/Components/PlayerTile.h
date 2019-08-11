//
// Created by Brandon Martin on 7/4/19.
//

#ifndef CURSEN_PLAYERTILE_H
#define CURSEN_PLAYERTILE_H

#include "Cursen/Components/AggregateComponent.h"
#include "Cursen/Components/Label.h"
#include "Cursen/Components/Box.h"
#include "Uno/GameObjects/Player.h"

class PlayerTile : public cursen::AggregateComponent
{

public:

    PlayerTile();
    PlayerTile(cursen::Vect2 pos);
    ~PlayerTile();

    void initialize() override;
    void clear();
    void injectPlayer(const Player& player);

    void setForeground(const cursen::Color& color) override ;

    void highlight();
    void unhighlight();
    void flash();

    void setCardCount(size_t count);
    void setName(const std::string& name);
    void setColor(PlayerColor color);

private:

    cursen::AlarmHandle flash_handle;
    cursen::Box border;
    cursen::Label player_name;
    cursen::Label player_cards;
    std::string name;
    PlayerColor color;

};


#endif //CURSEN_PLAYERTILE_H
