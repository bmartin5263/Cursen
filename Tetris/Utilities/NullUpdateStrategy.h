//
// Created by Brandon Martin on 9/29/19.
//

#ifndef CURSEN_NULLUPDATESTRATEGY_H
#define CURSEN_NULLUPDATESTRATEGY_H


#include "UpdateStrategy.h"

class NullUpdateStrategy : public UpdateStrategy
{
public:

    bool update(Tetris& tetris) override;
    void reset() override;

};


#endif //CURSEN_NULLUPDATESTRATEGY_H
