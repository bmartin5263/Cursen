//
// Created by Brandon Martin on 7/4/19.
//

#include <Uno/Constants.h>
#include "PlayerTile.h"

using namespace cursen;

// Color(17) == blue
// Color(52) == red
// Color(22) == green
// Color(136) == yellow

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
    border.setFill(Content::TRANSPARENT);
    addRelative(border);

    player_name.initialize();
    player_name.setPosition(Vect2(1,1));
    addRelative(player_name);

    player_cards.initialize();
    player_cards.setPosition(Vect2(1, 2));
    player_cards.setTextAlignment(TextAlignment::RIGHT);
    player_cards.setSize(Vect2(12, 1));
    addRelative(player_cards);

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
    setColor(player.getColor());
    setForeground(Player::ConvertColor(player.getColor()));
    setName(player.getName());
    setCardCount(player.getHandSize());
}

void PlayerTile::setCardCount(size_t count)
{
    std::string str(std::to_string(count) + " Cards");
    Constants::padLeft(str, Constants::MAX_NAME_LEN);
    player_cards.setText(str);
}

void PlayerTile::setName(const std::string& name)
{
    std::string str(name);
    Constants::padRight(str, Constants::MAX_NAME_LEN);
    player_name.setText(str);
}

void PlayerTile::setForeground(const cursen::Color& color)
{
    border.setForeground(color);
    player_name.setForeground(color);
    player_cards.setForeground(color);
}

void PlayerTile::highlight()
{
    switch (color)
    {
        case PlayerColor::BLUE:
            player_name.setBackground(Color(17));
            player_cards.setBackground(Color(17));
            break;
        case PlayerColor::RED:
            player_name.setBackground(Color(52));
            player_cards.setBackground(Color(52));
            break;
        case PlayerColor::GREEN:
            player_name.setBackground(Color(22));
            player_cards.setBackground(Color(22));
            break;
        case PlayerColor::YELLOW:
            player_name.setBackground(Color(136));
            player_cards.setBackground(Color(136));
            break;
        case PlayerColor::PURPLE:
            player_name.setBackground(Color(53));
            player_cards.setBackground(Color(53));
            break;
        case PlayerColor::ORANGE:
            player_name.setBackground(Color(58));
            player_cards.setBackground(Color(58));
            break;
        case PlayerColor::GRAY:
            player_name.setBackground(Color::BLACK);
            player_cards.setBackground(Color::BLACK);
            break;
    }
}

void PlayerTile::unhighlight()
{
    player_name.setBackground(Color::BLACK);
    player_cards.setBackground(Color::BLACK);
}

void PlayerTile::setColor(PlayerColor color)
{
    this->color = color;
}
