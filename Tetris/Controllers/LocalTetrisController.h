//
// Created by Brandon Martin on 10/8/19.
//

#ifndef CURSEN_LOCALTETRISCONTROLLER_H
#define CURSEN_LOCALTETRISCONTROLLER_H


#include "TetrisController.h"

class LocalTetrisController : public TetrisController
{
public:

    void pressDrop() override;
    void pressLeft() override;
    void pressRight() override;

    void handleDrop() override;

};


#endif //CURSEN_LOCALTETRISCONTROLLER_H
