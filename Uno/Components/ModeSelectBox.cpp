//
// Created by Brandon Martin on 4/10/19.
//

#include "Uno/Network/NetworkManager.h"
#include "Uno/Network/Client.h"
#include "ModeSelectBox.h"
#include "Cursen/Drawing/CursesManager.h"
#include "Uno/Forms/LobbyForm.h"

using namespace cursen;

ModeSelectBox::ModeSelectBox() {

}

ModeSelectBox::ModeSelectBox(const Vect2 &pos) : AggregateComponent(pos) {

}

void ModeSelectBox::initialize() {

    border.initialize();
    border.setPosition(Vect2(0,0));
    border.setSize(Vect2(36, 21));
    addRelative(border);

    console_box.initialize();
    console_box.setSize(Vect2(36, 3));
    console_box.setPosition(Vect2(0,5));
    console_box.setLowerRight(ACS_RTEE);
    console_box.setLowerLeft(ACS_LTEE);
    console_box.setUpperRight(ACS_RTEE);
    console_box.setUpperLeft(ACS_LTEE);
    addRelative(console_box);

    console_message.initialize();
    console_message.setPosition(Vect2(1,6));
    console_message.setForeground(Color::YELLOW);
    console_message.setText("Please Enter Your Name");
    addRelative(console_message);

    player_stage.initialize();
    player_stage.setPosition(Vect2(1,1));
    player_stage.setForeground(Color::GRAY);
    player_stage.setStageColor(Color::BLUE);
    player_stage.getTextField().setPlaceholderText("Your Name");
    addRelative(player_stage);

    local_button.initialize();
    local_button.setPosition(Vect2(1,8));
    local_button.setLength(34);
    local_button.setText("Local Singleplayer");
    local_button.setEnabled(false);
    addRelative(local_button);

    host_button.initialize();
    host_button.setPosition(Vect2(1,11));
    host_button.setLength(34);
    host_button.setText("Host Multiplayer");
    host_button.setEnabled(false);
    addRelative(host_button);

    join_button.initialize();
    join_button.setPosition(Vect2(1,14));
    join_button.setLength(34);
    join_button.setText("Join Multiplayer");
    join_button.setEnabled(false);
    addRelative(join_button);

    exit_button.initialize();
    exit_button.setPosition(Vect2(1,17));
    exit_button.setLength(34);
    exit_button.setText("Exit");
    exit_button.setEnabled(false);
    addRelative(exit_button);

    ip_entry.initialize();
    ip_entry.setSize(Vect2(50, 1));
    ip_entry.setPosition(Vect2(2,15));
    ip_entry.setForeground(Color::WHITE);
    ip_entry.setEnabled(false);
    addRelative(ip_entry);

    join_progress.initialize();
    join_progress.setForeground(Color::MAGENTA);
    join_progress.setPosition(Vect2(22,15));
    addRelative(join_progress);

    ip_entry_box.initialize();
    ip_entry_box.setPosition(Vect2(11,12));
    ip_entry_box.setDrawOrder(20);
    ip_entry_box.setHidden(true);

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
    console_message.setForeground(Color::YELLOW);
    console_message.setText(text);
}

void ModeSelectBox::setWarning(const std::string &text) {
    console_message.setForeground(Color::MAGENTA);
    console_message.setText(text);
}

void ModeSelectBox::startIpEntry(std::function<void(const Event &)> callback)
{
    join_button.setForeground(Color::MAGENTA);
    //ip_entry.setEnabled(true);
    mode_cursor.setEnabled(false);
    //console_message.setText("Please Enter Host IP");
    ip_entry_box.setHidden(false);
    onEnterPress(callback);
}

std::string ModeSelectBox::getIpAddress()
{
    std::string addr = ip_entry_box.getText();
    ip_entry_box.setText("");
    ip_entry_box.setHidden(true);
    join_button.setText("Connecting    ");
    return addr;
}

void ModeSelectBox::cleanIpEntry()
{
    join_button.setForeground(Color::WHITE);
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

