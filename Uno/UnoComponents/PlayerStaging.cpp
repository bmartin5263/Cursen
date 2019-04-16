//
// Created by Brandon Martin on 4/10/19.
//

#include "PlayerStaging.h"
#include "../Constants.h"
#include "../Forms/LobbyForm.h"

PlayerStaging::PlayerStaging() :
    spinning(false)
{

}

PlayerStaging::PlayerStaging(const Size &loc) :
        AggregateComponent(loc), spinning(false)
{

}

void PlayerStaging::initialize() {

    border.initialize();
    border.setPosition(Size(0,0));
    border.setSize(Size(70,10));
    border.setLowerRight(ACS_RTEE);
    border.setUpperRight(ACS_RTEE);
    border.setLowerLeft(ACS_LTEE);
    border.setUpperLeft(ACS_LTEE);
    addRelative(&border);

    for (Stage& stage : stages) {
        stage.initialize();
    }

    stages[0].setPosition(Size(1,1));
    stages[0].setEnabled(false);
    stages[0].setStageColor(Constants::COLORS[0]);
    addRelative(&stages[0]);

    stages[1].setPosition(Size(35,1));
    stages[1].setEnabled(false);
    stages[1].setStageColor(Constants::COLORS[1]);
    addRelative(&stages[1]);

    stages[2].setPosition(Size(1,5));
    stages[2].setEnabled(false);
    stages[2].setStageColor(Constants::COLORS[2]);
    addRelative(&stages[2]);

    stages[3].setPosition(Size(35,5));
    stages[3].setEnabled(false);
    stages[3].setStageColor(Constants::COLORS[3]);
    addRelative(&stages[3]);

    stageCursor.mapComponent(&stages[0], ArrowMap(&stages[1], &stages[2], &stages[1], &stages[2]));
    stageCursor.mapComponent(&stages[1], ArrowMap(&stages[0], &stages[3], &stages[0], &stages[3]));
    stageCursor.mapComponent(&stages[2], ArrowMap(&stages[3], &stages[0], &stages[3], &stages[0]));
    stageCursor.mapComponent(&stages[3], ArrowMap(&stages[2], &stages[1], &stages[2], &stages[1]));
    stageCursor.setEnabled(false);
}

void PlayerStaging::clear() {
    for (int i = 0 ; i < Lobby::MAX_PLAYERS; i++) {
        stages[i].clear();
    }
}

void PlayerStaging::startSearching() {
    for (Stage& s : stages) {
        s.searchIfEmtpy();
    }
}

void PlayerStaging::stopSearching() {
    for (Stage& s : stages) {
        s.stopSearch();
    }
}

void PlayerStaging::update(const Lobby &lobby) {
    int i;
    for (i = 0; i < lobby.getNumPlayers(); i++) {
        stages[i].setPlayer(*lobby.getPlayer(i));
    }
    for (; i < Lobby::MAX_PLAYERS; i++) {
        if (!lobby.isSearching()) {
            stages[i].clear();
        }
    }
}

void PlayerStaging::enableCursor() {
    stageCursor.moveTo(&stages[0]);
    stageCursor.setEnabled(true);
    stages[0].setTextToCancel();
}

void PlayerStaging::setCallBacks(LobbyForm* lobby) {
    stages[0].onClick(std::bind(&LobbyForm::removePlayer, lobby, 0));
    stages[1].onClick(std::bind(&LobbyForm::removePlayer, lobby, 1));
    stages[2].onClick(std::bind(&LobbyForm::removePlayer, lobby, 2));
    stages[3].onClick(std::bind(&LobbyForm::removePlayer, lobby, 3));
}

void PlayerStaging::disableCursor() {
    stageCursor.setEnabled(false);
}