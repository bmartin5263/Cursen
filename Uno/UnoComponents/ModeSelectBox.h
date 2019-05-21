//
// Created by Brandon Martin on 4/10/19.
//

#ifndef CURSEN_MODESELECTBOX_H
#define CURSEN_MODESELECTBOX_H


#include "Components/AggregateComponent.h"
#include "Components/Label.h"
#include "Components/Box.h"
#include "Components/Button.h"
#include "Cursor/Cursor.h"
#include "Stage.h"
#include <functional>

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

    void setText(const std::string &text) override;
    void setHidden(bool value) override;

    void setMessage(const std::string& text);
    void setWarning(const std::string& text);

private:

    cursen::Box border;
    Stage player_stage;
    cursen::Box console_box;
    cursen::Label console_message;
    cursen::Button local_button;
    cursen::Button host_button;
    cursen::Button join_button;
    cursen::Button exit_button;
    cursen::Cursor mode_cursor;

};


#endif //CURSEN_MODESELECTBOX_H
