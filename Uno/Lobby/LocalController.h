//
// Created by Brandon Martin on 5/20/19.
//

#ifndef CURSEN_LOCALCONTROLLER_H
#define CURSEN_LOCALCONTROLLER_H


#include "LobbyController.h"

class LocalController : public LobbyController
{
public:
    LocalController(LobbyForm* form);
    void initialize() override;
    void destroy() override;
    void clickStart() override;
    void clickAddAI() override;
    void clickSearch() override;
    void clickKick() override;
    void clickClose() override;
    void clickChangeColor() override;
    void sendChat() override;
    void kickPlayer(int id) override;

};


#endif //CURSEN_LOCALCONTROLLER_H
