//
// Created by Brandon Martin on 4/10/19.
//

#ifndef CURSEN_STAGE_H
#define CURSEN_STAGE_H


#include <Components/TextField.h>
#include "Components/AggregateComponent.h"
#include "Components/Box.h"
#include "Components/Label.h"
#include "Components/TwirlProgress.h"
#include "../GameObjects/Player.h"

class Lobby;

class Stage : public AggregateComponent {

public:

    Stage();
    Stage(const Vect2& pos);

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
    void setStageColor(const Color& stageColor);

    TextField& getTextField();

    std::string getText() override;

    void setEnabled(bool value) override;

private:

    Box border;
    Label playerName;
    Label points;
    TwirlProgress search_progress;
    TextField textField;
    Color stage_color;

};


#endif //CURSEN_STAGE_H
