//
// Created by Brandon Martin on 5/20/19.
//

#ifndef CURSEN_HOSTCONTROLLER_H
#define CURSEN_HOSTCONTROLLER_H


#include "LobbyController.h"

class HostController : public LobbyController
{
public:

    void clickStart() override;
    void clickAddAI() override;
    void clickSearch() override;
    void clickKick() override;
    void clickClose() override;
    void clickChangeColor() override;
    void clickChat() override;

};


#endif //CURSEN_HOSTCONTROLLER_H