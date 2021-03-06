//
// Created by Brandon Martin on 4/10/19.
//

#include "PlayerStaging.h"
#include "Uno/Constants.h"
#include "Uno/Forms/LobbyForm.h"

PlayerStaging::PlayerStaging()
{

}

PlayerStaging::PlayerStaging(const cursen::Vect2& loc) :
        AggregateComponent(loc)
{

}

void PlayerStaging::initialize()
{
    border.initialize();
    border.setPosition(cursen::Vect2(0, 0));
    border.setSize(cursen::Vect2(70, 10));
    border.setLowerRight(ACS_RTEE);
    border.setUpperRight(ACS_RTEE);
    border.setLowerLeft(ACS_LTEE);
    border.setUpperLeft(ACS_LTEE);
    addRelative(border);

    for (Stage& stage : stages)
    {
        stage.initialize();
    }

    stages[0].setPosition(cursen::Vect2(1, 1));
    stages[0].setStageColor(cursen::Color::GRAY);
    addRelative(stages[0]);

    stages[1].setPosition(cursen::Vect2(35, 1));
    stages[1].setStageColor(cursen::Color::GRAY);
    addRelative(stages[1]);

    stages[2].setPosition(cursen::Vect2(1, 5));
    stages[2].setStageColor(cursen::Color::GRAY);
    addRelative(stages[2]);

    stages[3].setPosition(cursen::Vect2(35, 5));
    stages[3].setStageColor(cursen::Color::GRAY);
    addRelative(stages[3]);

    stageCursor.mapComponent(&stages[0], cursen::ArrowMap(&stages[1], &stages[2], &stages[1], &stages[2]));
    stageCursor.mapComponent(&stages[1], cursen::ArrowMap(&stages[0], &stages[3], &stages[0], &stages[3]));
    stageCursor.mapComponent(&stages[2], cursen::ArrowMap(&stages[3], &stages[0], &stages[3], &stages[0]));
    stageCursor.mapComponent(&stages[3], cursen::ArrowMap(&stages[2], &stages[1], &stages[2], &stages[1]));
    stageCursor.setEnabled(false);
}

void PlayerStaging::clear()
{
    for (int i = 0; i < Lobby::MAX_PLAYERS; i++)
    {
        stages[i].clear();
    }
}

void PlayerStaging::startSearching(int start)
{
    for (int i = start; i < Lobby::MAX_PLAYERS; ++i)
    {
        stages[i].searchIfEmtpy();
    }
}

void PlayerStaging::stopSearching(int start)
{
    for (int i = start; i < Lobby::MAX_PLAYERS; ++i)
    {
        stages[i].stopSearch();
    }
}

void PlayerStaging::update(Lobby& lobby)
{
    if (!stageCursor.isEnabled()) {

        Player* players = lobby.getPlayers();

        int i;
        for (i = 0; i < lobby.getNumPlayers(); i++)
        {
            stages[i].setPlayer(players[i]);
            stages[i].setCursable(true);
        }

        for (; i < Lobby::MAX_PLAYERS; i++)
        {
            if (!lobby.isSearching())
            {
                stages[i].clear();
                stages[i].setCursable(false);
            }
        }
    }
}

void PlayerStaging::enableCursor()
{
    stageCursor.moveTo(&stages[0]);
    stageCursor.setEnabled(true);
    stages[0].setTextToCancel();
}

void PlayerStaging::setCallBacks(LobbyForm* lobby)
{
    stages[0].onClick([=]() { lobby->selectPlayerToRemove(0); });
    stages[1].onClick([=]() { lobby->selectPlayerToRemove(1); });
    stages[2].onClick([=]() { lobby->selectPlayerToRemove(2); });
    stages[3].onClick([=]() { lobby->selectPlayerToRemove(3); });
}

void PlayerStaging::disableCursor()
{
    stageCursor.setEnabled(false);
}

Stage& PlayerStaging::getStage(int index)
{
    return stages[index];
}
