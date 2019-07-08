//
// Created by Brandon Martin on 7/4/19.
//

#include "PlayerTile.h"

using namespace cursen;

PlayerTile::PlayerTile() :
    AggregateComponent()
{

}

PlayerTile::PlayerTile(cursen::Vect2 pos) :
    AggregateComponent(pos)
{

}

void PlayerTile::initialize()
{
    border.initialize();
    border.setSize(Vect2(14, 4));
    border.setFill(Content::INVISIBLE);
    addRelative(&border);

    player_name.initialize();
    player_name.setPosition(Vect2(1,1));
    addRelative(&player_name);

    player_cards.initialize();
    player_cards.setPosition(Vect2(1, 2));
    player_cards.setTextAlignment(TextAlignment::RIGHT);
    player_cards.setSize(Vect2(12, 1));
    addRelative(&player_cards);

    clear();
}

void PlayerTile::clear()
{
    border.setForeground(Color::GRAY);
    player_cards.setForeground(Color::GRAY);
    player_name.setForeground(Color::GRAY);
    player_name.setText("No Player");
    player_cards.emplaceText("");
}

void PlayerTile::injectPlayer(const Player& player)
{
    setForeground(Player::ConvertColor(player.getColor()));
    setName(player.getName());
    setCardCount(player.getHandSize());
}

void PlayerTile::setCardCount(size_t count)
{
    if (count == 1) player_cards.emplaceText("1 Card");
    else player_cards.emplaceText(std::to_string(count) + " Cards");
}

void PlayerTile::setName(const std::string& name)
{
    player_name.setText(name);
}

void PlayerTile::setForeground(const cursen::Color& color)
{
    border.setForeground(color);
    player_name.setForeground(color);
    player_cards.setForeground(color);
}
