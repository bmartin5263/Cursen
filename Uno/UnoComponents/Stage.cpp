//
// Created by Brandon Martin on 4/10/19.
//

#include "Stage.h"
#include "Uno/GameObjects/Player.h"
#include "Uno/Constants.h"

Stage::Stage() :
    stage_color(cursen::Color::PURPLE)
{

}

Stage::Stage(const cursen::Vect2 &pos) : AggregateComponent(pos),
    stage_color(cursen::Color::PURPLE)
{

}

void Stage::initialize() {
    border.initialize();
    border.setSize(cursen::Vect2(34,4));
    addRelative(&border);

    playerName.initialize();
    playerName.setText("No Player");
    playerName.setPosition(cursen::Vect2(1,1));
    addRelative(&playerName);

    points.initialize();
    points.setText("Points: 0");
    points.setPosition(cursen::Vect2(1, 2));
    addRelative(&points);

    search_progress.initialize();
    search_progress.setPosition(cursen::Vect2(11, 1));
    addRelative(&search_progress);

    textField.initialize();
    textField.setPosition(cursen::Vect2(1,1));
    textField.setForeground(stage_color);
    textField.setSize(cursen::Vect2(Constants::MAX_NAME_LEN, 1));
    textField.setHidden(true);
    //textField.setActiveBackgroundColor(cursen::Color::RED);
    addRelative(&textField);

    onCursor(std::bind(&Stage::hoverOn, this));
    offCursor(std::bind(&Stage::hoverOff, this));
}

void Stage::setStageColor(const cursen::Color &stageColor) {
    this->stage_color = stageColor;
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
    playerName.setText(player.getName());
    points.setText("Points: " + std::to_string(player.getPoints()));

    setStageColor(Player::ConvertColor(player.getColor()));
    setForeground(stage_color);
    if (search_progress.isSpinning()) {
        search_progress.stop();
    }

    setEnabled(true);
}

void Stage::hoverOn() {
    setForeground(cursen::Color::WHITE);
}

void Stage::hoverOff() {
    setForeground(stage_color);
}

void Stage::setTextToCancel() {
    playerName.setText("Cancel");
    points.setText("");
}

void Stage::activateTextField() {
    textField.setHidden(false);
    textField.setEnabled(true);
    textField.setForeground(stage_color);
}

void Stage::deactivateTextField() {
    textField.setHidden(true);
    textField.setEnabled(false);
    //textField.deactivate();
}

cursen::TextField &Stage::getTextField() {
    return textField;
}

std::string Stage::getText() {
    return playerName.getText();
}

void Stage::setEnabled(bool value) {
    Component::setEnabled(value);
    border.setEnabled(value);
    playerName.setEnabled(value);
    points.setEnabled(value);
    search_progress.setEnabled(value);
}
