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

class ModeSelectBox : public AggregateComponent {

public:

    ModeSelectBox();
    ModeSelectBox(const Size& pos);

    void onLocalClick( std::function<void()> f);
    void onHostClick( std::function<void()> f);
    void onJoinClick( std::function<void()> f);
    void onExitClick( std::function<void()> f);

    Stage& getMainPlayerStage();

    void initialize() override;

    void start();

    void setText(const std::string &text) override;
    void setHidden(bool value) override;

    void setMessage(const std::string& text);
    void setWarning(const std::string& text);

private:

    Box border;
    Box console_box;
    Label console_message;
    Stage player_stage;
    Button local_button;
    Button host_button;
    Button join_button;
    Button exit_button;

    Cursor mode_cursor;

};


#endif //CURSEN_MODESELECTBOX_H
