//
// Created by Brandon Martin on 7/5/19.
//

#ifndef CURSEN_MATCHCONTROLLERS_H
#define CURSEN_MATCHCONTROLLERS_H

#include "MatchHostController.h"
#include "MatchLocalController.h"
#include "MatchClientController.h"

class MatchControllers
{
public:

    static MatchHostController matchHostController;
    static MatchLocalController matchLocalController;
    static MatchClientController matchClientController;

};

#endif //CURSEN_MATCHCONTROLLERS_H
