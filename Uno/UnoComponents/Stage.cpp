//
// Created by Brandon Martin on 4/10/19.
//

#include "Stage.h"

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

void Stage::toggleSearch() {
    if (search_progress.isSpinning()) {
        search_progress.stop();
        playerName.setText("No Player");
        points.setText("Points: 0");
    }
    else if (!isEnabled()) {
        search_progress.start();
        playerName.setText("Searching");
        points.setText("");
    }
}
