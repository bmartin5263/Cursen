//
// Created by Brandon Martin on 4/10/19.
//

#include "ModeSelectBox.h"

ModeSelectBox::ModeSelectBox() {

}

ModeSelectBox::ModeSelectBox(const Size &pos) : AggregateComponent(pos) {

}

void ModeSelectBox::initialize() {

    border.initialize();
    border.setPosition(Size(0,0));
    border.setSize(Size(36, 21));
    addRelative(&border);

    console_box.initialize();
    console_box.setSize(Size(36, 3));
    console_box.setPosition(Size(0,5));
    console_box.setLowerRight(ACS_RTEE);
    console_box.setLowerLeft(ACS_LTEE);
    console_box.setUpperRight(ACS_RTEE);
    console_box.setUpperLeft(ACS_LTEE);
    addRelative(&console_box);

    console_message.initialize();
    console_message.setPosition(Size(1,6));
    console_message.setForeground(Color::YELLOW);
    console_message.setText("Please Enter Your Name");
    addRelative(&console_message);

    player_stage.initialize();
    player_stage.setPosition(Size(1,1));
    player_stage.setForeground(Color::GRAY);
    player_stage.setStageColor(Color::BLUE);
    addRelative(&player_stage);

    local_button.initialize();
    local_button.setPosition(Size(1,8));
    local_button.setLength(34);
    local_button.setText("Local Singleplayer");
    local_button.setEnabled(false);
    addRelative(&local_button);

    host_button.initialize();
    host_button.setPosition(Size(1,11));
    host_button.setLength(34);
    host_button.setText("Host Multiplayer");
    host_button.setEnabled(false);
    addRelative(&host_button);

    join_button.initialize();
    join_button.setPosition(Size(1,14));
    join_button.setLength(34);
    join_button.setText("Join Multiplayer");
    join_button.setEnabled(false);
    addRelative(&join_button);

    exit_button.initialize();
    exit_button.setPosition(Size(1,17));
    exit_button.setLength(34);
    exit_button.setText("Exit");
    exit_button.setEnabled(false);
    addRelative(&exit_button);

    mode_cursor.moveTo(&local_button);
    mode_cursor.mapComponent(&local_button, ArrowMap(nullptr, &exit_button, nullptr, &host_button));
    mode_cursor.mapComponent(&host_button, ArrowMap(nullptr, &local_button, nullptr, &join_button));
    mode_cursor.mapComponent(&join_button, ArrowMap(nullptr, &host_button, nullptr, &exit_button));
    mode_cursor.mapComponent(&exit_button, ArrowMap(nullptr, &join_button, nullptr, &local_button));
    mode_cursor.setEnabled(false);
}

void ModeSelectBox::onLocalClick(std::function<void()> f) {
    local_button.onClick(f);
}

void ModeSelectBox::onHostClick(std::function<void()> f) {
    host_button.onClick(f);
}

void ModeSelectBox::onJoinClick(std::function<void()> f) {
    join_button.onClick(f);
}

void ModeSelectBox::onExitClick(std::function<void()> f) {
    exit_button.onClick(f);
}

void ModeSelectBox::setText(const std::string &text) {
    console_message.setText(text);
}

void ModeSelectBox::setHidden(bool value) {
    AggregateComponent::setHidden(value);
    mode_cursor.setEnabled(!value);
}

Stage &ModeSelectBox::getMainPlayerStage() {
    return player_stage;
}

void ModeSelectBox::start() {
    player_stage.getTextField().setText("");
    player_stage.getTextField().deactivate();
    player_stage.getTextField().setHidden(true);
    player_stage.getTextField().detachEnterPress();
    local_button.setEnabled(true);
    join_button.setEnabled(true);
    host_button.setEnabled(true);
    exit_button.setEnabled(true);
    mode_cursor.setEnabled(true);
    console_message.setText("Welcome to Uno! Select a Mode");
}

