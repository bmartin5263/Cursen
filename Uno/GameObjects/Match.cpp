//
// Created by Brandon Martin on 7/5/19.
//

#include <cassert>
#include "Match.h"

Match::Match(Player* players, int numPlayers, int my_id) :
    num_players(numPlayers), current_player_index(0), current_player_id(players[0].getId()), my_id(my_id),
    waitingForWildCardColor(false)
{
    for (int i = 0; i < num_players; ++i)
    {
        this->players[i] = players[i];
    }
    current_player_index = rand() % num_players;
    current_player_id = players[current_player_index].getId();
}

Deck& Match::getDeck()
{
    return deck;
}

Player* Match::getPlayers()
{
    return players;
}

int Match::getNumPlayers()
{
    return num_players;
}

size_t Match::getDeckSize()
{
    return deck.size();
}

int Match::getMyId()
{
    return my_id;
}

Player& Match::getMyPlayer()
{
    for (int i = 0; i < num_players; ++i)
    {
        if (players->getId() == my_id) return players[i];
    }
    assert(false);
    return players[0];
}

bool Match::canDrawCard(int player_id)
{
    return true;
}

void Match::drawCard(int player_id)
{
    assert(canDrawCard(player_id));
    Card c = deck.popCard();
    getPlayerById(player_id).getHand().add(c);
}

Player& Match::getPlayerById(int player_id)
{
    for (auto& player : players)
    {
        if (player.getId() == player_id) return player;
    }
    assert(false);
    return players[0];
}

void Match::drawCardByIndex(int player_index)
{
    Card c = deck.popCard();
    players[player_index].getHand().add(c);
}

std::string Match::getCurrentPlayerName()
{
    return players[current_player_index].getName();
}

int Match::getId(int player_index)
{
    return players[player_index].getId();
}

int Match::getIndex(int player_id)
{
    for (int i = 0; i < num_players; ++i)
    {
        if (players[i].getId() == player_id) return i;
    }
    return -1;
}

bool Match::canPlayCard(int player_id, int card_index)
{
    return true;
    if (!waitingForWildCardColor && current_player_id == player_id && pile.size() > 0)
    {
        Hand& hand = getPlayerById(player_id).getHand();
        size_t hand_size = hand.size();
        if (card_index >= 0 && card_index < hand_size)
        {
            const Card& card = hand.get(card_index);
            const Card& top_card = pile.peekCard();
            if (card.isWild() && !hand.hasPlayableCardFor(card))
            {
                return true;
            }
            else
            {
                if (card.getColor() == top_card.getColor() || card.getValue() == top_card.getValue())
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void Match::playCard(int player_id, int card_index)
{
    Player& p = getPlayerById(player_id);
    const Card& card = p.getHand().get(card_index);
    pile.pushCard(card);
    if (card.isWild())
    {
        waitingForWildCardColor = true;
    }
}

Deck& Match::getPile()
{
    return pile;
}

bool Match::isWaitingForWildColor()
{
    return waitingForWildCardColor;
}

void Match::setWildColor(CardColor color)
{
    const Card& top = pile.peekCard();
    Card new_card = top.changeColor(color);
    pile.popCard();
    pile.pushCard(new_card);
    waitingForWildCardColor = false;
}

int Match::currentTurnId()
{
    return current_player_id;
}
