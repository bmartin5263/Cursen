//
// Created by Brandon Martin on 4/10/19.
//

#include "PlayerStaging.h"
#include "../Constants.h"

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
    addRelative(&stages[0]);

    stages[1].setPosition(Size(35,1));
    stages[1].setEnabled(false);
    addRelative(&stages[1]);

    stages[2].setPosition(Size(1,5));
    stages[2].setEnabled(false);
    addRelative(&stages[2]);

    stages[3].setPosition(Size(35,5));
    stages[3].setEnabled(false);
    addRelative(&stages[3]);
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
        stages[i].setForegroundAll(Constants::COLORS[i]);
    }
    for (; i < Lobby::MAX_PLAYERS; i++) {
        stages[i].clear();
    }
}
