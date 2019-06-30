//
// Created by Brandon Martin on 4/10/19.
//

#ifndef CURSEN_MODESELECTBOX_H
#define CURSEN_MODESELECTBOX_H

#include <functional>

#include "Cursen/Components/AggregateComponent.h"
#include "Cursen/Components/Label.h"
#include "Cursen/Components/Box.h"
#include "Cursen/Components/Button.h"
#include "Cursen/Cursor/Cursor.h"
#include "Stage.h"

class LobbyForm;
class ModeSelectBox : public cursen::AggregateComponent {

public:

    ModeSelectBox();
    ModeSelectBox(const cursen::Vect2& pos);

    void onLocalClick(std::function<void()> f);
    void onHostClick(std::function<void()> f);
    void onJoinClick(std::function<void()> f);
    void onExitClick(std::function<void()> f);

    Stage& getMainPlayerStage();

    void initialize() override;

    void start();

    void startIpEntry(std::function<void(const cursen::Event &)> callback);
    std::string getIpAddress();
    void cleanIpEntry();

    void setText(const std::string &text) override;
    void setHidden(bool value) override;

    void setMessage(const std::string& text);
    void setWarning(const std::string& text);

    void setLobby(LobbyForm* lobby);
    void enableCursor();

    std::string getPlayerName();
    void setPlayerName(const std::string& name);

private:

    LobbyForm* lobbyForm;
    cursen::Box border;
    Stage player_stage;
    cursen::Box console_box;
    cursen::Label console_message;
    cursen::Button local_button;
    cursen::Button host_button;
    cursen::Button join_button;
    cursen::Button exit_button;
    cursen::Cursor mode_cursor;
    cursen::TextField ip_entry;
    cursen::TwirlProgress join_progress;
    std::string player_name;

};


#endif //CURSEN_MODESELECTBOX_H
