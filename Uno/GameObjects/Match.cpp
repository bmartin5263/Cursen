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
        if (players[i].getId() == my_id) {
            return players[i];
        }
    }
    assert(false);
    return players[0];
}

bool Match::canDrawCard(int player_id)
{
    return (deck.size() > 0);
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
    if (!waitingForWildCardColor && (current_player_id == player_id || true) && (pile.size() > 0 || true))
    {
        Hand& hand = getPlayerById(player_id).getHand();
        size_t hand_size = hand.size();
        if (card_index >= 0 && card_index < hand_size)
        {
            const Card& card = hand.get(card_index);
            if (pile.size() > 0)
            {
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
            else
            {
                return true;
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

ClientMatch Match::convertToClientMatch(int client_id)
{
    ClientMatch clientMatch;
    clientMatch.pile = this->pile;
    clientMatch.current_player_index = this->current_player_index;
    clientMatch.waitingForWildCardColor = this->waitingForWildCardColor;
    clientMatch.num_players = this->num_players;
    clientMatch.my_id = client_id;
    clientMatch.deck_size = deck.size();
    for (int i = 0; i < num_players; i++)
    {
        clientMatch.players[i] = this->players[i];
    }
    return clientMatch;
}

void Match::readFromClientMatch(ClientMatch clientMatch)
{
    current_player_id = -1;
    current_player_index = clientMatch.current_player_index;
    pile = clientMatch.pile;
    waitingForWildCardColor = clientMatch.waitingForWildCardColor;
    deck.clear();
    for (int i = 0; i < clientMatch.deck_size; ++i) deck.pushCard(Card());
    my_id = clientMatch.my_id;
    num_players = clientMatch.num_players;
    int i = 0;
    for (; i < num_players; ++i)
    {
        players[i] = clientMatch.players[i];
    }
    for (; i < Lobby::MAX_PLAYERS; ++i)
    {
        players[i].clear();
    }

}

bool Match::hasId(int player_id)
{
    for (auto& player : players)
    {
        if (player.getId() == player_id) return true;
    }
    return false;
}

Card Match::peekCardFromDeck()
{
    return deck.peekCard();
}

void Match::popCardFromDeck()
{
    deck.popCard();
}

Card Match::getCardFromPlayer(int index, int card_index)
{
    return players[index].getHand().get(card_index);
}

void Match::removeCardFromPlayer(int index, int card_index)
{
    players[index].getHand().remove(card_index);
}

void Match::pushCardToPile(Card card)
{
    pile.pushCard(card);
    if (card.isWild()) waitingForWildCardColor = true;
}
