//
// Created by Brandon Martin on 4/10/19.
//

#ifndef CURSEN_PLAYERSTAGING_H
#define CURSEN_PLAYERSTAGING_H

#include "Cursen/Components/AggregateComponent.h"
#include "Cursen/Components/Box.h"
#include "Cursen/Cursor/Cursor.h"
#include "Stage.h"
#include "Uno/GameObjects/Lobby.h"

class LobbyForm;

class PlayerStaging : public cursen::AggregateComponent {

public:

    PlayerStaging();
    PlayerStaging(const cursen::Vect2& loc);

    void initialize() override;
    void setCallBacks(LobbyForm* lobby);

    void update(Lobby& lobby);
    void clear();

    void enableCursor();
    void disableCursor();

    void startSearching(int start);
    void stopSearching(int start);

    Stage& getStage(int index);

private:

    cursen::Box border;
    Stage stages[Lobby::MAX_PLAYERS];
    cursen::Cursor stageCursor;

};


#endif //CURSEN_PLAYERSTAGING_H
