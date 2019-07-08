//
// Created by Brandon Martin on 7/5/19.
//

#include "MatchLocalController.h"
#include "Uno/GameObjects/Deck.h"

void MatchLocalController::clickCard()
{

}

void MatchLocalController::pressDraw()
{

}

void MatchLocalController::start()
{
    Match* match = getMatchForm()->getMatch();
    Deck& deck = match->getDeck();
    Deck::InitializeDeck(deck);
    getMatchForm()->updatePlayers();
    getMatchForm()->setDeckMeterSize(Deck::SIZE);
    getMatchForm()->setDeckMeterCount(deck.size());
    getMatchForm()->setHandName(match->getMyPlayer().getName());
}
