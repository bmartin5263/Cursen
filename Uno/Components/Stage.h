//
// Created by Brandon Martin on 4/10/19.
//

#ifndef CURSEN_STAGE_H
#define CURSEN_STAGE_H

#include "Cursen/Components/TextField.h"
#include "Cursen/Components/AggregateComponent.h"
#include "Cursen/Components/Box.h"
#include "Cursen/Components/Label.h"
#include "Cursen/Components/TwirlProgress.h"
#include "Uno/GameObjects/Player.h"

class Lobby;

class Stage : public cursen::AggregateComponent {

public:

    Stage();
    Stage(const cursen::Vect2& pos);

    void initialize() override;

    void clear();
    void setPlayer(const Player& player);
    void setTextToCancel();

    void hoverOn();
    void hoverOff();

    void activateTextField();
    void deactivateTextField();

    void searchIfEmtpy();
    void stopSearch();

    void setHidden(bool value) override;
    void setStageColor(const cursen::Color& stageColor);

    cursen::TextField& getTextField();

    std::string getText() override;

    void setEnabled(bool value) override;

private:

    cursen::Box border;
    cursen::Label playerName;
    cursen::Label points;
    cursen::TwirlProgress search_progress;
    cursen::TextField textField;
    cursen::Color stage_color;

};


#endif //CURSEN_STAGE_H
