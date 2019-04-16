//
// Created by Brandon Martin on 4/10/19.
//

#include "Stage.h"
#include "../GameObjects/Player.h"
#include "../Constants.h"

Stage::Stage() :
    stage_color(Color::PURPLE)
{

}

Stage::Stage(const Size &pos) : AggregateComponent(pos),
    stage_color(Color::PURPLE)
{

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

    textField.initialize();
    textField.setPosition(Size(1,1));
    textField.setForeground(stage_color);
    textField.setSize(Size(Constants::MAX_NAME_LEN, 1));
    textField.setHidden(true);
    addRelative(&textField);

    onCursor(std::bind(&Stage::hoverOn, this));
    offCursor(std::bind(&Stage::hoverOff, this));
}

void Stage::setStageColor(const Color &stageColor) {
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
    setEnabled(true);
    playerName.setText(player.getName());
    points.setText("Points: " + std::to_string(player.getPoints()));
    setForeground(stage_color);
    if (search_progress.isSpinning()) {
        search_progress.stop();
    }
}

void Stage::hoverOn() {
    setForeground(Color::WHITE);
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

TextField &Stage::getTextField() {
    return textField;
}

std::string Stage::getText() {
    return playerName.getText();
}

void Stage::setEnabled(bool value) {
    bool text_field_enabled = textField.isEnabled();
    AggregateComponent::setEnabled(value);
    textField.setEnabled(text_field_enabled);
}
