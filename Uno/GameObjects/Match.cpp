//
// Created by Brandon Martin on 7/5/19.
//

#include <cassert>
#include "Match.h"

Match::Match(Player* players, int numPlayers, int my_id, int my_index) :
    num_players(numPlayers), current_player_index(0), current_player_id(players[0].getId()), my_id(my_id),
    my_index(my_index), consecutive_passes(0), waitingForWildCardColor(false), reversed(false)
{
    for (int i = 0; i < num_players; ++i)
    {
        this->players[i] = players[i];
    }
    current_player_index = rand() % num_players;
    current_player_id = players[current_player_index].getId();
}

Match& Match::operator=(const Match& other)
{
    if (&other != this)
    {
        for (int i = 0; i < 4; ++i) players[i] = other.players[i];
        this->deck = other.deck;
        this->pile = other.pile;
        this->num_players = other.num_players;
        this->current_player_index = other.current_player_index;
        this->current_player_id = other.current_player_id;
        this->consecutive_passes = other.consecutive_passes;
        this->waitingForWildCardColor = other.waitingForWildCardColor;
        this->reversed = other.reversed;
    }
    return *this;
}


int Match::CalculateNextTurn(int current_turn, int num_players, bool reversed)
{
    if (reversed)
    {
        if (current_turn == 0) current_turn = num_players - 1;
        else current_turn--;
    }
    else
    {
        current_turn = (current_turn + 1) % num_players;
    }
    return current_turn;
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
    return players[getMyIndex()];
}

bool Match::canDrawCard(int player_id)
{
    return deck.size() > 0 && player_id == current_player_id;
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

bool Match::canPlayCard(int player_index, int card_index)
{
    // Can't play a card if a wild card needs a color or if its not your turn or if you need to draw
    if (!waitingForWildCardColor && current_player_index == player_index && players[player_index].getForceDraws() == 0)
    {
        Hand& hand = players[player_index].getHand();
        size_t hand_size = hand.size();

        // Ensure card index is valid
        if (card_index >= 0 && card_index < hand_size)
        {
            // Verify the card is legal
            const Card& card = hand.get(card_index);
            const Card& top_card = pile.peekCard();

            // Wild cards can only be played if the player has no other legal cards
            if (card.getValue() == CardValue::PLUS_4)
            {
                if (!hand.hasPlayableCardFor(top_card)) return true;
            }
            else
            {
                if (card.getColor() == top_card.getColor() || card.getValue() == top_card.getValue() || card.isWild())
                {
                    return true;
                }
            }
        }
    }
    return false;
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

int Match::getCurrentTurnId()
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
    clientMatch.reversed = this->reversed;
    clientMatch.consecutive_passes = this->consecutive_passes;
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
    reversed = clientMatch.reversed;
    consecutive_passes = clientMatch.consecutive_passes;
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
    if (deck.size() == 0)
    {
        for (auto& player : players) player.clearForceDraws();
    }
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
    if (card.isWild())
    {
        waitingForWildCardColor = true;
    }
    consecutive_passes = 0;
}

bool Match::currentPlayerHasEmptyHand()
{
    return players[current_player_index].getHand().empty();
}

bool Match::pileIsEmpty()
{
    return pile.empty();
}

int Match::getCurrentTurn()
{
    return current_player_index;
}

int Match::advanceTurn()
{
    //if (pile.size() == 1) return current_player_index;
    current_player_index = Match::CalculateNextTurn(current_player_index, num_players, reversed);
    current_player_id = players[current_player_index].getId();
    return current_player_index;
}

bool Match::aiTurn()
{
    return players[current_player_index].isAI();
}

bool Match::myTurn()
{
    return my_index == current_player_index;
}

int Match::getMyIndex()
{
    return my_index;
}

Player& Match::getCurrentPlayer()
{
    return players[current_player_index];
}

Player& Match::getPlayer(int player_index)
{
    return players[player_index];
}

int Match::getForceDrawAmount()
{
    // TODO: peek next player then add the amount, instead of checking every time
    const Card& top_card = pile.peekCard();
    if (top_card.getValue() == CardValue::PLUS_2) return 2;
    else if (top_card.getValue() == CardValue::PLUS_4) return 4;
    return 0;
}

int Match::peekNextTurn()
{
    return Match::CalculateNextTurn(current_player_index, num_players, reversed);
}

bool Match::isSkipCard()
{
    return pile.peekCard().getValue() == CardValue::SKIP;
}

bool Match::isReverseCard()
{
    return pile.peekCard().getValue() == CardValue::REVERSE;
}

void Match::reverseTurnOrder()
{
    this->reversed = !this->reversed;
}

bool Match::isTurnOrderReversed()
{
    return this->reversed;
}

bool Match::canPass(int player_index)
{
    return current_player_index == player_index && deck.size() == 0 && !players[player_index].hasPlayableCard(pile.peekCard());
}

void Match::pass()
{
    consecutive_passes++;
}

int Match::getConsecutivePasses()
{
    return consecutive_passes;
}

/*
 * Player players[Lobby::MAX_PLAYERS];
    Deck deck;
    Deck pile;
    int num_players;
    int current_player_index;
    int current_player_id;
    int my_id;
    int consecutive_passes;
    bool waitingForWildCardColor;
    bool reversed;
 */
size_t Match::serialize(char* const buffer) const
{
    size_t written = 0;
    written += deck.serialize(buffer + written);
    written += pile.serialize(buffer + written);
    written += Serializable::Serialize(buffer + written, num_players);
    for (int i = 0; i < num_players; ++i)
    {
        written += players[i].safeSerialize(buffer + written, false);
    }
    written += Serializable::Serialize(buffer + written, current_player_index);
    written += Serializable::Serialize(buffer + written, current_player_id);
    written += Serializable::Serialize(buffer + written, consecutive_passes);
    written += Serializable::Serialize(buffer + written, waitingForWildCardColor);
    written += Serializable::Serialize(buffer + written, reversed);
    return written;
}

size_t Match::deserialize(const char* const buffer)
{
    size_t read = 0;
    read += deck.deserialize(buffer + read);
    read += pile.deserialize(buffer + read);
    read += Serializable::Deserialize(buffer + read, num_players);
    for (int i = 0; i < num_players; ++i)
    {
        read += players[i].deserialize(buffer + read);
    }
    read += Serializable::Deserialize(buffer + read, current_player_index);
    read += Serializable::Deserialize(buffer + read, current_player_id);
    read += Serializable::Deserialize(buffer + read, consecutive_passes);
    read += Serializable::Deserialize(buffer + read, waitingForWildCardColor);
    read += Serializable::Deserialize(buffer + read, reversed);
    return read;
}

size_t Match::sizeOf() const
{
    return sizeof(Match);
}