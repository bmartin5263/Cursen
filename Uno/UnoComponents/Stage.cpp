//
// Created by Brandon Martin on 4/10/19.
//

#include "Stage.h"
#include "../GameObjects/Player.h"

Stage::Stage() {

}

Stage::Stage(const Size &pos) : AggregateComponent(pos) {

}

void Stage::initialize() {
    border.initialize();
    border.setSize(Size(34,4));
    addRelative(&border);

    playerName.initialize();
    playerName.setText("No Player");
    playerName.setPosition(Size(1,1));
    addRelative(&playerName);

    points.initialize();
    points.setText("Points: 0");
    points.setPosition(Size(1, 2));
    addRelative(&points);

    search_progress.initialize();
    search_progress.setPosition(Size(11, 1));
    addRelative(&search_progress);
}

void Stage::searchIfEmtpy() {
    if (!isEnabled()) {
        search_progress.start();
        playerName.setText("Searching");
        points.setText("");
    }
}

void Stage::stopSearch() {
    if (search_progress.isSpinning()) {
        search_progress.stop();
        playerName.setText("No Player");
        points.setText("Points: 0");
    }
}

void Stage::setHidden(bool value) {
    border.setHidden(value);
    playerName.setHidden(value);
    points.setHidden(value);
}

void Stage::clear() {
    setEnabled(false);
    playerName.setText("No Player");
    points.setText("Points: 0");
}

void Stage::setPlayer(const Player & player) {
    setEnabled(true);
    playerName.setText(player.getName());
    points.setText("Points: " + std::to_string(player.getPoints()));
}
