//
// Created by Brandon Martin on 4/10/19.
//

#ifndef CURSEN_PLAYERSTAGING_H
#define CURSEN_PLAYERSTAGING_H


#include "Components/AggregateComponent.h"
#include "Components/Box.h"
#include "Cursor/Cursor.h"
#include "Stage.h"
#include "../GameObjects/Lobby.h"

class LobbyForm;

class PlayerStaging : public AggregateComponent {

public:

    PlayerStaging();
    PlayerStaging(const Vect2& loc);

    void initialize() override;
    void setCallBacks(LobbyForm* lobby);

    void update(const Lobby& lobby);
    void clear();

    void enableCursor();
    void disableCursor();

    void startSearching();
    void stopSearching();

private:

    Box border;
    Stage stages[Lobby::MAX_PLAYERS];
    Cursor stageCursor;
    bool spinning;

};


#endif //CURSEN_PLAYERSTAGING_H
