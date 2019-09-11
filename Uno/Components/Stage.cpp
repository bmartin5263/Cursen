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
    addRelative(border);

    playerName.initialize();
    playerName.setText("No Player");
    playerName.setPosition(cursen::Vect2(1,1));
    addRelative(playerName);

    points.initialize();
    points.setText("");
    points.setPosition(cursen::Vect2(1, 2));
    addRelative(points);

    search_progress.initialize();
    search_progress.setPosition(cursen::Vect2(11, 1));
    addRelative(search_progress);

    textField.initialize();
    textField.setPosition(cursen::Vect2(1,1));
    textField.setForeground(stage_color);
    textField.setSize(cursen::Vect2(Constants::MAX_NAME_LEN, 1));
    addRelative(textField);

    onCursor([&]() { this->hoverOn(); });
    offCursor([&]() { this->hoverOff(); });

    stage_color = cursen::Color::GRAY;
    setForeground(stage_color);

    this->searching = false;
}

Stage& Stage::operator=(const Stage& other)
{
    if (this != &other)
    {
        this->playerName.setText(other.playerName.getText());
        this->points.setText(other.points.getText());
        this->stage_color = other.stage_color;
        setCursable(other.isCursable());
        setForeground(stage_color);
    }
    return *this;
}


void Stage::setStageColor(const cursen::Color &stageColor)
{
    this->stage_color = stageColor;
}

void Stage::searchIfEmtpy() {
    if (!searching) {
        search_progress.start();
        playerName.setText("Searching");
        points.setText("");
        searching = true;
    }
}

void Stage::stopSearch() {
    if (searching) {
        search_progress.stop();
        playerName.setText("No Player");
        points.setText("");
        searching = false;
    }
}

void Stage::setHidden(bool value) {
    border.setHidden(value);
    playerName.setHidden(value);
    points.setHidden(value);
}

void Stage::clear() {
    setCursable(false);
    playerName.setText("No Player");
    points.setText("");
    stage_color = cursen::Color::GRAY;
    setForeground(stage_color);
}

void Stage::setPlayer(const Player & player) {
    //playerName.setText(player.getName() + " : " + std::to_string(player.getId()));
    if (player.isDummy())
    {
        playerName.setText("Player Joining...");
        points.setText("");
        setStageColor(cursen::Color::GRAY);
    }
    else
    {
        playerName.setText(player.getName());
        points.setText("Points: " + std::to_string(player.getPoints()));
        setStageColor(Player::ConvertColor(player.getColor()));
    }
    setForeground(stage_color);
    if (search_progress.isSpinning()) {
        search_progress.stop();
    }
    searching = false;
    setCursable(true);
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

std::string Stage::getText() const {
    return playerName.getText();
}