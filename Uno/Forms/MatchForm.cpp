//
// Created by Brandon Martin on 6/30/19.
//

#include <cassert>

#include <Uno/Match/MatchControllers.h>
#include <Uno/Data/DataManager.h>
#include "MatchForm.h"
#include "Cursen/CursenApplication.h"
#include "Uno/Match/FSM/MatchState.h"
#include "Uno/Match/FSM/MatchFSM.h"
#include "Uno/GameObjects/Match.h"

using namespace cursen;

MatchForm::MatchForm(LobbyType type, Match* match) :
        Form(cursen::Vect2(70, 33)), match(match), card_index(-1), hand_index(0)
{
    switch (type)
    {
        case LobbyType::LOCAL:
            controller = &MatchControllers::matchLocalController;
            break;
        case LobbyType::HOST:
            controller = &MatchControllers::matchHostController;
            break;
        case LobbyType::JOIN:
            controller = &MatchControllers::matchClientController;
            break;
    }
    controller->setMatchForm(this);
}

MatchForm::~MatchForm()
{
    delete match;
}

void MatchForm::initialize()
{
    welcome.initialize();
    welcome.setPosition(Vect2(0,0));
    welcome.setText("Welcome to the Match!");
    welcome.onEscapePress([](const Event e) { CursenApplication::CloseForm(); });
    welcome.onDeletePress([&](const Event e) {
        front_card.shrink();
    });

    console.initialize();
    console.setText("Welcome!");

    lowerBorder.initialize();
    lowerBorder.setPosition(Vect2(0, 6));

    deck_label.initialize();
    deck_label.setPosition(Vect2(1, 8));
    deck_label.setText("Deck:");

    hand_label.initialize();
    hand_label.setPosition(Vect2(1, 24));
    setHandName("Unknown");

    handMeter.initialize();
    handMeter.setPosition(Vect2(55, 24));

    deck_size.initialize();
    deck_size.setPosition(Vect2(1, 9));
    deck_size.setText("0 Cards");

    hand_box.initialize();
    hand_box.setPosition(Vect2(0, 23));
    hand_box.setSize(Vect2(70, 3));
    hand_box.setUpperRight(CursesManager::RTEE);
    hand_box.setLowerRight(CursesManager::RTEE);
    hand_box.setLowerLeft(CursesManager::LTEE);
    hand_box.setUpperLeft(CursesManager::LTEE);
    hand_box.setFill(Content::TRANSPARENT);
    hand_box.setDrawOrder(lowerBorder.getDrawOrder() + 1);

    deckMeter.initialize();
    deckMeter.setPosition(Vect2(1, 11));

    p0Tile.initialize();
    p0Tile.setPosition(Vect2(55, 7));

    p1Tile.initialize();
    p1Tile.setPosition(Vect2(55, 11));

    p2Tile.initialize();
    p2Tile.setPosition(Vect2(55, 15));

    p3Tile.initialize();
    p3Tile.setPosition(Vect2(55, 19));

    leftCard.initialize();
    leftCard.setPosition(Vect2(2, 27));
    leftCard.setLeft();

    rightCard.initialize();
    rightCard.setPosition(Vect2(64, 27));
    rightCard.setRight();

    int x = 7;
    for (int i = 0; i < 14; i++)
    {
        card_array[i].initialize();
        card_array[i].setPosition(Vect2(x + (4 * i), 27));
        card_array[i].setHidden(true);
        card_array[i].onClick([&]() { this->clickCard(); });
    }

    back_card.initialize();
    back_card.setPosition(Vect2(27,8));
    back_card.setHidden(true);

    front_card.initialize();
    front_card.setPosition(Vect2(29,10));
    front_card.drawOnTopOf(back_card);
    //front_card.shrinkCompletely();
    front_card.setHidden(true);

    tile_array[0] = &p0Tile;
    tile_array[1] = &p1Tile;
    tile_array[2] = &p2Tile;
    tile_array[3] = &p3Tile;

    start();

    onEnterPress([&](const Event& event) { this->enterPress(event); });
    onArrowPress([&](const Event& event) { this->arrowPress(event); });
    onKeyPress([&](const Event& event) { this->keyPress(event); });

    onOpen([]() { DataManager::SetContext(Context::ContextMatch); });

    placeCardAnimation.setForm(this);

    wildColorAnimation.setContinuous(false);
    wildColorAnimation.setLoops(2);
    wildColorAnimation.setVariableTime(false);
    wildColorAnimation.setFrameDuration(.06);
    wildColorAnimation.add([this]() { front_card.setForeground(Color::RED); });
    wildColorAnimation.add([this]() { front_card.setForeground(Color::ORANGE); });
    wildColorAnimation.add([this]() { front_card.setForeground(Color::YELLOW); });
    wildColorAnimation.add([this]() { front_card.setForeground(Color::GREEN); });
    wildColorAnimation.add([this]() { front_card.setForeground(Color::BLUE); });
    wildColorAnimation.onEnd([this]() {
        front_card.setForeground(Card::ConvertToColor(match->getPile().peekCard().getColor()));
        setState(&MatchFSM::waitingToBeginState);
    });
}

void MatchForm::clickCard()
{
    controller->clickCard();
}

void MatchForm::start()
{
    controller->start();
}

Match* MatchForm::getMatch()
{
    assert(match != nullptr);
    return match;
}

void MatchForm::updatePlayers()
{
    assert(match != nullptr);
    int num_players = match->getNumPlayers();
    Player* players = match->getPlayers();
    int i;
    for (i = 0; i < num_players; ++i)
    {
        tile_array[i]->injectPlayer(players[i]);
    }
    for (; i < Lobby::MAX_PLAYERS; ++i)
    {
        tile_array[i]->clear();
    }
}


void MatchForm::setDeckMeterCount(size_t size)
{
    deckMeter.setCardCount(size);
    if (size == 1) deck_size.setText("1 Card");
    deck_size.setText(std::to_string(size) + " Cards");
}

void MatchForm::setDeckMeterSize(size_t size)
{
    deckMeter.setDeckSize(size);
}

void MatchForm::pressDraw()
{
    controller->pressDraw();
}

void MatchForm::setHandName(std::string name)
{
    hand_label.setText(name + "'s Hand");
}

void MatchForm::dealCards()
{
    state = &MatchFSM::animationState;
    console.setMessage("Dealing Cards...");
    dealCardsEventController.run(this, (size_t)match->getNumPlayers(), 7);
}

void MatchForm::setConsoleMessage(std::string msg)
{
    this->console.setText(msg);
}

void MatchForm::setConsoleWarning(std::string  msg)
{
    this->console.setWarning(msg);
}

void MatchForm::enterPress(const cursen::Event& event)
{
    state->pressEnter(*this);
}

void MatchForm::setState(const MatchState* state)
{
    this->state = state;
}

MatchController* MatchForm::getController()
{
    return controller;
}

const MatchState* MatchForm::getState()
{
    return state;
}

void MatchForm::waitToBegin()
{
    controller->waitToBegin();
}

void MatchForm::beginGame()
{
    closeForm();
}

void MatchForm::updateHand()
{
    Player& p = match->getMyPlayer();
    Hand& hand = p.getHand();
    int start = 14 * hand_index;
    size_t hand_size = hand.size();
    while (start > hand_size && hand_index > 0)
    {
        --hand_index;
        start = 14 * hand_index;
    }
    int count = 0;
    for (; start < hand_size; ++start)
    {
        const Card& c = hand.get(start);
        card_array[count].setHidden(false);
        card_array[count++].injectCard(c);
        if (count == 14) break;
    }
    for (; count < 14; ++count)
    {
        card_array[count].clear();
    }

    if (hand_size == 0) {
        card_array[card_index].hoverOff();
        card_index = -1;
    }
    else if (card_index == -1)
    {
        card_index = 0;
        card_array[card_index].hoverOn();
    }
    handMeter.update((int)hand_size, hand_index);
}

void MatchForm::drawCardByIndex(int index)
{
    int id = match->getId(index);
    match->drawCardByIndex(index);
    tile_array[index]->setCardCount(match->getPlayers()[index].getHandSize());
    setDeckMeterCount(match->getDeckSize());
    if (id == match->getMyId())
    {
        updateHand();
    }
}

void MatchForm::drawCard(int player_id)
{
    int index = match->getIndex(player_id);
    int new_hand_index = (int)(match->getMyPlayer().getHand().size() / 14);
    match->drawCard(player_id);
    tile_array[index]->setCardCount(match->getPlayerById(player_id).getHandSize());
    setDeckMeterCount(match->getDeckSize());
    if (player_id == match->getMyId())
    {
        card_array[card_index].hoverOff();
        card_index = ((int)match->getMyPlayer().getHandSize() - 1) % 14;
        card_array[card_index].hoverOn();
        hand_index = new_hand_index;
        updateHand();
    }
}

void MatchForm::playCard(int player_id, int card_index)
{
    //int index = match->getIndex(player_id);

    if (front_card.hasCardInjected())
    {
        back_card.setValuesFrom(front_card);
    }

    match->playCard(player_id, card_index);

    front_card.injectCard(match->getPile().peekCard());

    front_card.shrinkCompletely();
    front_card.setHidden(true);
    placeCardAnimation.run();

//    if (player_id == match->getMyId())
//    {
//        updateHand();
//        card_array[card_index].hoverOff();
//        card_index = (int)(match->getMyPlayer().getHandSize() % 14) - 1;
//        card_array[card_index].hoverOn();
//    }
}

void MatchForm::arrowPress(const cursen::Event& event)
{
    if (card_index > -1)
    {
        if (event.arrowPress.left)
        {
            if (card_index > 0)
            {
                card_array[card_index--].hoverOff();
                card_array[card_index].hoverOn();
            }
            else if (hand_index > 0)
            {
                card_array[card_index].hoverOff();
                card_index = 13;
                card_array[card_index].hoverOn();
                hand_index--;
                updateHand();
            }
        }
        else if (event.arrowPress.right)
        {
            int max_hand_index = (int)(match->getMyPlayer().getHand().size() / 14);
            int upper_limit = (int)(match->getMyPlayer().getHandSize() % 14) - 1;
            if (card_index < 13)
            {
                if (hand_index == max_hand_index)
                {
                    if (card_index < upper_limit)
                    {
                        card_array[card_index++].hoverOff();
                        card_array[card_index].hoverOn();
                    }
                }
                else
                {
                    card_array[card_index++].hoverOff();
                    card_array[card_index].hoverOn();
                }
            }
            else
            {
                if (hand_index < max_hand_index)
                {
                    card_array[card_index].hoverOff();
                    card_index = 0;
                    card_array[card_index].hoverOn();
                    hand_index++;
                    updateHand();
                }
            }
        }
    }
}

void MatchForm::keyPress(const cursen::Event& event)
{
    switch (event.key.code)
    {
        case 'D':
        case 'd':
            state->pressD(*this);
            break;
        case ' ':
            state->pressSpace(*this);
            break;
        case 'q':
            front_card.grow();
            break;
        case 'B':
        case 'b':
            state->pressB(*this);
            break;
        case 'Y':
        case 'y':
            state->pressY(*this);
            break;
        case 'R':
        case 'r':
            state->pressR(*this);
            break;
        case 'G':
        case 'g':
            state->pressG(*this);
            break;
        default:
            break;
    }
}

int MatchForm::getSelectedCardIndex()
{
    return (hand_index * 14) + card_index;
}

GiantCard& MatchForm::getFrontCard()
{
    return front_card;
}

void MatchForm::wildColorChange(CardColor color)
{
    match->setWildColor(color);
    front_card.injectCard(match->getPile().peekCard());
    wildColorAnimation.start(false);
}
