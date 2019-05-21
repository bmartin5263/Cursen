//
// Created by Brandon Martin on 5/20/19.
//

#ifndef CURSEN_CLIENTCONTROLLER_H
#define CURSEN_CLIENTCONTROLLER_H


#include "LobbyController.h"

class ClientController : public LobbyController
{
public:

    ClientController(LobbyForm* form);
    void initialize() override;
    void destroy() override;
    void update() override;
    void clickStart() override;
    void clickAddAI() override;
    void clickSearch() override;
    void clickKick() override;
    void clickClose() override;
    void clickChangeColor() override;
    void clickChat() override;

};


#endif //CURSEN_CLIENTCONTROLLER_H
