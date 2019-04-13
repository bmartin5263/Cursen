//
// Created by Brandon Martin on 4/10/19.
//

#include "PlayerStaging.h"

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

    p1Stage.initialize();
    p1Stage.setPosition(Size(1,1));
    p1Stage.setEnabled(false);
    addRelative(&p1Stage);

    p2Stage.initialize();
    p2Stage.setPosition(Size(35,1));
    p2Stage.setEnabled(false);
    addRelative(&p2Stage);

    p3Stage.initialize();
    p3Stage.setPosition(Size(1,5));
    p3Stage.setEnabled(false);
    addRelative(&p3Stage);

    p4Stage.initialize();
    p4Stage.setPosition(Size(35,5));
    p4Stage.setEnabled(false);
    addRelative(&p4Stage);
}

void PlayerStaging::startSearching() {
    p1Stage.searchIfEmtpy();
    p2Stage.searchIfEmtpy();
    p3Stage.searchIfEmtpy();
    p4Stage.searchIfEmtpy();
}

void PlayerStaging::stopSearching() {
    p1Stage.stopSearch();
    p2Stage.stopSearch();
    p3Stage.stopSearch();
    p4Stage.stopSearch();
}
