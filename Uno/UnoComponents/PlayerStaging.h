//
// Created by Brandon Martin on 4/10/19.
//

#ifndef CURSEN_PLAYERSTAGING_H
#define CURSEN_PLAYERSTAGING_H


#include "Components/AggregateComponent.h"
#include "Components/Box.h"
#include "Stage.h"
#include "../GameObjects/Lobby.h"

class PlayerStaging : public AggregateComponent {

public:

    PlayerStaging();
    PlayerStaging(const Size& loc);

    void initialize() override;

    void update(const Lobby& lobby);
    void clear();

    void startSearching();
    void stopSearching();

private:

    Box border;
    Stage stages[Lobby::MAX_PLAYERS];
    bool spinning;

};


#endif //CURSEN_PLAYERSTAGING_H
