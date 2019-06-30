//
// Created by Brandon Martin on 4/10/19.
//

#include "Uno/Network/NetworkManager.h"
#include "Uno/Network/Client.h"
#include "ModeSelectBox.h"
#include "Cursen/Drawing/CursesManager.h"
#include "Uno/Forms/LobbyForm.h"

ModeSelectBox::ModeSelectBox() {

}

ModeSelectBox::ModeSelectBox(const cursen::Vect2 &pos) : AggregateComponent(pos) {

}

void ModeSelectBox::initialize() {

    border.initialize();
    border.setPosition(cursen::Vect2(0,0));
    border.setSize(cursen::Vect2(36, 21));
    addRelative(&border);

    console_box.initialize();
    console_box.setSize(cursen::Vect2(36, 3));
    console_box.setPosition(cursen::Vect2(0,5));
    console_box.setLowerRight(ACS_RTEE);
    console_box.setLowerLeft(ACS_LTEE);
    console_box.setUpperRight(ACS_RTEE);
    console_box.setUpperLeft(ACS_LTEE);
    addRelative(&console_box);

    console_message.initialize();
    console_message.setPosition(cursen::Vect2(1,6));
    console_message.setForeground(cursen::Color::YELLOW);
    console_message.setText("Please Enter Your Name");
    addRelative(&console_message);

    player_stage.initialize();
    player_stage.setPosition(cursen::Vect2(1,1));
    player_stage.setForeground(cursen::Color::GRAY);
    player_stage.setStageColor(cursen::Color::BLUE);
    addRelative(&player_stage);

    local_button.initialize();
    local_button.setPosition(cursen::Vect2(1,8));
    local_button.setLength(34);
    local_button.setText("Local Singleplayer");
    local_button.setEnabled(false);
    addRelative(&local_button);

    host_button.initialize();
    host_button.setPosition(cursen::Vect2(1,11));
    host_button.setLength(34);
    host_button.setText("Host Multiplayer");
    host_button.setEnabled(false);
    addRelative(&host_button);

    join_button.initialize();
    join_button.setPosition(cursen::Vect2(1,14));
    join_button.setLength(34);
    join_button.setText("Join Multiplayer");
    join_button.setEnabled(false);
    addRelative(&join_button);

    exit_button.initialize();
    exit_button.setPosition(cursen::Vect2(1,17));
    exit_button.setLength(34);
    exit_button.setText("Exit");
    exit_button.setEnabled(false);
    addRelative(&exit_button);

    ip_entry.initialize();
    ip_entry.setSize(cursen::Vect2(50, 1));
    ip_entry.setPosition(cursen::Vect2(2,15));
    ip_entry.setForeground(cursen::Color::WHITE);
    ip_entry.setEnabled(false);
    addRelative(&ip_entry);

    join_progress.initialize();
    join_progress.setForeground(cursen::Color::RED);
    join_progress.setPosition(cursen::Vect2(22,15));
    addRelative(&join_progress);

    mode_cursor.moveTo(&local_button);
    mode_cursor.mapComponent(&local_button, cursen::ArrowMap(nullptr, &exit_button, nullptr, &host_button));
    mode_cursor.mapComponent(&host_button, cursen::ArrowMap(nullptr, &local_button, nullptr, &join_button));
    mode_cursor.mapComponent(&join_button, cursen::ArrowMap(nullptr, &host_button, nullptr, &exit_button));
    mode_cursor.mapComponent(&exit_button, cursen::ArrowMap(nullptr, &join_button, nullptr, &local_button));
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
    ip_entry.setHidden(true);
    join_progress.setHidden(true);
}

Stage &ModeSelectBox::getMainPlayerStage() {
    return player_stage;
}

void ModeSelectBox::start() {
    player_stage.getTextField().setText("");
    player_stage.getTextField().setHidden(true);
    player_stage.getTextField().detachEnterPress();
    local_button.setEnabled(true);
    join_button.setEnabled(true);
    host_button.setEnabled(true);
    exit_button.setEnabled(true);
    mode_cursor.setEnabled(true);
    setMessage("Welcome to Uno! Select a Mode");
}

void ModeSelectBox::setMessage(const std::string &text) {
    console_message.setForeground(cursen::Color::YELLOW);
    console_message.setText(text);
}

void ModeSelectBox::setWarning(const std::string &text) {
    console_message.setForeground(cursen::Color::RED);
    console_message.setText(text);
}

void ModeSelectBox::startIpEntry(std::function<void(const cursen::Event &)> callback)
{
    join_button.setForeground(cursen::Color::RED);
    ip_entry.setEnabled(true);
    mode_cursor.setEnabled(false);
    console_message.setText("Please Enter Host IP");
    onEnterPress(callback);
}

std::string ModeSelectBox::getIpAddress()
{
    detachEnterPress();
    std::string addr = ip_entry.getText();
    ip_entry.setText("");
    ip_entry.setEnabled(false);
    join_button.setText("Connecting    ");
    return addr;
}

void ModeSelectBox::cleanIpEntry()
{
    join_button.setForeground(cursen::Color::WHITE);
    join_button.setText("Join Multiplayer");
}
void ModeSelectBox::setLobby(LobbyForm* lobby)
{
    this->lobbyForm = lobby;
}

void ModeSelectBox::enableCursor()
{
    this->mode_cursor.setEnabled(true);
}

std::string ModeSelectBox::getPlayerName()
{
    return player_name;
}

void ModeSelectBox::setPlayerName(const std::string& name)
{
    this->player_name = name;
}

