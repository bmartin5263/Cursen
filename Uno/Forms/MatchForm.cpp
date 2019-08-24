//
// Created by Brandon Martin on 6/30/19.
//

#include <cassert>

#include <Uno/Match/MatchControllers.h>
#include <Uno/Data/DataManager.h>
#include <Uno/Match/MatchReturnData.h>
#include "MatchForm.h"
#include "Cursen/CursenApplication.h"
#include "Uno/Match/FSM/MatchInputState.h"
#include "Uno/Match/FSM/MatchFSM.h"
#include "Uno/GameObjects/Match.h"

using namespace cursen;

MatchForm::MatchForm(LobbyType type, Match match) :
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
    controller->reset();
    controller->setMatchForm(this);
}

MatchForm::~MatchForm()
{
}

void MatchForm::exit(std::string message, bool kicked)
{
    MatchReturnData* returnData = new MatchReturnData(message, kicked);
    for (int i = 0; i < match.getNumPlayers(); ++i) {
        match.getPlayer(i).getHand().clear();
        returnData->setPlayer(i, match.getPlayer(i));
    }
    closeForm(returnData);
}

void MatchForm::initialize()
{
    welcome.initialize();
    welcome.setPosition(Vect2(0,0));
    welcome.setText("Welcome to the Match!");
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

    onEnterPress([&](const Event& event) { this->enterPress(event); });
    onArrowPress([&](const Event& event) { this->arrowPress(event); });
    onKeyPress([&](const Event& event) { this->keyPress(event); });

    onOpen([]() { DataManager::SetContext(Context::ContextMatch); });

    placeCardAnimation.setForm(this);
    skip_animation.setForm(this);
    reverse_animation.setForm(this);
    winner_animation.setForm(this);
    point_tally_animation.setForm(this);

    wildColorAnimation.setInfinite(false);
    wildColorAnimation.setLoops(2);
    wildColorAnimation.setVariableTime(false);
    wildColorAnimation.setFrameDuration(.06);
    wildColorAnimation.add([this]() { front_card.setForeground(Color::RED); });
    wildColorAnimation.add([this]() { front_card.setForeground(Color::ORANGE); });
    wildColorAnimation.add([this]() { front_card.setForeground(Color::YELLOW); });
    wildColorAnimation.add([this]() { front_card.setForeground(Color::GREEN); });
    wildColorAnimation.add([this]() { front_card.setForeground(Color::BLUE); });
    wildColorAnimation.onEnd([this]() {
        front_card.setForeground(Card::ConvertToColor(match.getPile().peekCard().getColor()));
        advanceTurn();
    });

    wild_cards.reserve(14);
    wild_hand_cards_animation.setFrameDuration(.06);
    wild_hand_cards_animation.setVariableTime(false);
    wild_hand_cards_animation.add([this]() {
        for (auto card : wild_cards) card->setForeground(cursen::Color::RED);
    });
    wild_hand_cards_animation.add([this]() {
        for (auto card : wild_cards) card->setForeground(cursen::Color::ORANGE);
    });
    wild_hand_cards_animation.add([this]() {
        for (auto card : wild_cards) card->setForeground(cursen::Color::YELLOW);
    });
    wild_hand_cards_animation.add([this]() {
        for (auto card : wild_cards) card->setForeground(cursen::Color::GREEN);
    });
    wild_hand_cards_animation.add([this]() {
        for (auto card : wild_cards) card->setForeground(cursen::Color::BLUE);
    });
    wild_hand_cards_animation.add([this]() {
        for (auto card : wild_cards) card->setForeground(cursen::Color::LAVENDER);
    });
    wild_hand_cards_animation.start();

    start();
}

void MatchForm::clickCard()
{
    controller->clickCard();
}

void MatchForm::start()
{
    controller->start();
}

Match& MatchForm::getMatch()
{
    return match;
}

void MatchForm::updatePlayers()
{
    int num_players = match.getNumPlayers();
    Player* players = match.getPlayers();
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

void MatchForm::dealInitialCards()
{
    for (int i = 0; i < match.getNumPlayers(); ++i)
    {
        for (int j = 0; j < Deck::INITIAL_CARDS; ++j) {
            const Card& card = match.getDeck().popCard();
            match.getPlayers()[i].getHand().add(card);
        }
    }
}

void MatchForm::dealCards()
{
    setState(&MatchFSM::animationState);
    console.setMessage("Dealing Cards...");
    dealCardsEventController.run(this, (size_t)match.getNumPlayers(), Deck::INITIAL_CARDS, Deck::SIZE);
}

void MatchForm::interpretCard()
{
    if (match.isSkipCard())
    {
        int skipped_turn;
        if (match.getPile().size() == 1) skipped_turn = match.getCurrentTurn();
        else skipped_turn = match.peekNextTurn();
        console.setWarning("Skip Card Played! Skipping " + match.getPlayer(skipped_turn).getName() + "'s Turn");
        AlarmManager::SetTimeout([this, skipped_turn]() { skip_animation.run(skipped_turn); }, 1.5);
    }
    else if (match.isReverseCard())
    {
        console.setWarning("Reverse Card Played! Reversing Turn Order");
        match.reverseTurnOrder();
        AlarmManager::SetTimeout([this]() { reverse_animation.run(match.isTurnOrderReversed() ? -1 : 1, match.getPile().size() == 1); }, 1.5);
    }
    else if (match.isWaitingForWildColor())
    {
        if (match.myTurn())
        {
            console.setMessage("Wild Card! Select (B)lue, (R)ed, (Y)ellow, or (G)reen");
            setState(&MatchFSM::wildColorChoiceState);
        }
        else
        {
            console.setMessage("Wild Card! Waiting for " + match.getCurrentPlayerName() + " to Select a Color");
            if (match.aiTurn())
            {
                controller->handleAITurn();
            }
        }
    }
    else {
        advanceTurn(match.getPile().size() == 1 ? 0 : 1);
    }
}


void MatchForm::advanceTurn(int amount)
{
    if (match.currentPlayerHasEmptyHand())
    {
        controller->startGameoverEvent(match.getCurrentTurn());
    }
    else
    {
        tile_array[match.getCurrentTurn()]->unhighlight();
        int next_turn = match.getCurrentTurn();
        for (int i = 0; i < amount; ++i) next_turn = match.advanceTurn();
        tile_array[next_turn]->highlight();

        Player& current_player = match.getCurrentPlayer();
        current_player.addForceDraws(std::min(match.getForceDrawAmount(), (int)match.getDeckSize()));

        if (match.aiTurn())
        {
            console.setMessage(match.getCurrentPlayerName() + "'s Turn");
            ai_handle = AlarmManager::SetTimeout([this]() {
                controller->handleAITurn();
            }, 1.5);
        }
        else if (match.myTurn())
        {
            int force_draws = current_player.getForceDraws();
            if (force_draws > 0)
            {
                displayDrawMessage(force_draws);
            }
            else
            {
                displayTurnMessage();
            }
            setState(&MatchFSM::selectCardState);
        }
        else
        {
            console.setMessage(match.getCurrentPlayerName() + "'s Turn");
        }
    }
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

void MatchForm::setState(const MatchInputState* state)
{
    this->state = state;
}

MatchController* MatchForm::getController()
{
    return controller;
}

const MatchInputState* MatchForm::getState()
{
    return state;
}

void MatchForm::waitToBegin()
{
    controller->waitToBegin();
}

void MatchForm::beginGame(Card initial_card)
{
    match.getDeck().popCard();
    //match.pushCardToPile(Card(CardColor::GREEN, CardValue::REVERSE));
    match.pushCardToPile(initial_card);
    front_card.injectCard(match.getPile().peekCard(), match.isTurnOrderReversed());
    setDeckMeterCount(match.getDeckSize());
    card_index = 0;
    card_array[card_index].hoverOn();
    placeCardAnimation.run();
}

void MatchForm::updateHand(int player_index, size_t max)
{
    wild_cards.clear();
    Player& p = match.getPlayer(player_index);
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
        if (c.isWild()) wild_cards.push_back(&card_array[count]);
        card_array[count].setHidden(false);
        card_array[count++].injectCard(c);
        if (count == max) break;
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
//        card_index = 0;
//        card_array[card_index].hoverOn();
    }
    handMeter.update((int)hand_size, hand_index);
    setHandName(p.getName());
}

// Does not actually deal a card, just updates visuals
void MatchForm::effectDealCard(int index, size_t count, size_t deck_size)
{
    int id = match.getId(index);
    tile_array[index]->setCardCount(match.getPlayers()[index].getHandSize());
    setDeckMeterCount(deck_size);
    tile_array[index]->setCardCount(count);
    if (id == match.getMyId())
    {
        updateHand(match.getMyIndex(), count);
    }
}

void MatchForm::drawCardByIndex(int index)
{
    int id = match.getId(index);
    match.drawCardByIndex(index);
    tile_array[index]->setCardCount(match.getPlayers()[index].getHandSize());
    setDeckMeterCount(match.getDeckSize());
    if (id == match.getMyId())
    {
        updateHand(match.getMyIndex());
    }
}

void MatchForm::drawCard(int index, Card drawn_card)
{
    match.popCardFromDeck();
    Player& player = match.getPlayer(index);
    player.getHand().add(drawn_card);
    player.decrementForceDraws();

    tile_array[index]->setCardCount(match.getPlayers()[index].getHandSize());
    tile_array[index]->flash();

    setDeckMeterCount(match.getDeckSize());

    if (index == match.getMyIndex())
    {
        int new_hand_index = (int)((match.getMyPlayer().getHand().size() - 1) / 14);
        card_array[card_index].hoverOff();
        card_index = ((int)match.getMyPlayer().getHandSize() - 1) % 14;
        card_array[card_index].hoverOn();
        hand_index = new_hand_index;
        updateHand(index);
        if (player.getForceDraws() > 0) displayDrawMessage(player.getForceDraws());
        else displayTurnMessage();
    }
    if (match.aiTurn())
    {
        ai_handle = AlarmManager::SetTimeout([this]() {
            controller->handleAITurn();
        }, .5);
    }
}

void MatchForm::playCard(int index, int played_card_index, Card played_card)
{
    // Update Match State
    match.removeCardFromPlayer(index, played_card_index);
    match.pushCardToPile(played_card);

    // Update User Interface
    if (front_card.hasCardInjected())
    {
        back_card.setValuesFrom(front_card, match.isTurnOrderReversed());
    }
    front_card.injectCard(match.getPile().peekCard(), match.isTurnOrderReversed());
    size_t hand_size = match.getPlayers()[index].getHandSize();
    tile_array[index]->setCardCount(hand_size);
    if (index == match.getMyIndex())
    {
        updateHand(index);
        if (played_card_index == hand_size)
        {
            card_array[card_index].hoverOff();
            if (hand_size > 0)
            {
                card_array[--card_index].hoverOn();
            }
        }
    }
    placeCardAnimation.run();

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
                updateHand(match.getMyIndex());
            }
        }
        else if (event.arrowPress.right)
        {
            size_t hand_size = match.getMyPlayer().getHand().size();
            int max_hand_index = (int)(ceil(hand_size / 14.0) - 1);
            int upper_limit = (int)((hand_size - 1) % 14);
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
                    updateHand(match.getMyIndex());
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
        case 'P':
        case 'p':
            state->pressP(*this);
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
    match.setWildColor(color);
    front_card.injectCard(match.getPile().peekCard(), match.isTurnOrderReversed());
    console.setMessage("  WILD WILD WILD WILD WILD WILD WILD WILD WILD WILD WILD WILD WILD  ");
    wildColorAnimation.start();
}

void MatchForm::updateMatch(ClientMatch clientMatch)
{
    controller->updateMatch(clientMatch);
}

PlayerTile& MatchForm::getPlayerTile(int index)
{
    return *tile_array[index];
}

void MatchForm::displayDrawMessage(int force_draws)
{
    console.setWarning("Draw Card Played! (D)raw " + std::to_string(force_draws) + " Cards");
}

void MatchForm::displayTurnMessage()
{
    console.setMessage("Your Turn. Select a Card or (D)raw");
}

void MatchForm::passTurn(CardColor new_color)
{
    match.pass();
    if (new_color != CardColor::WHITE)
    {
        wildColorChange(new_color);
    }
    else
    {
        advanceTurn();
    }
}

void MatchForm::runWinnerAnimation(int winner)
{
    if (card_index != -1)
    {
        card_array[card_index].hoverOff();
        card_index = -1;
    }
    winner_animation.run(winner);
}

UnoConsole& MatchForm::getConsole()
{
    return console;
}

void MatchForm::tallyPoints(int winner)
{
    int points_won = 0;
    for (int i = 0; i < match.getNumPlayers(); ++i)
    {
        if (i != winner) points_won += match.getPlayer(i).getHand().getPointValue();
    }
    console.setMessage("Tallying Points");
    point_tally_animation.run(winner, points_won);
}