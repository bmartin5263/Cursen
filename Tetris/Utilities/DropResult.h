//
// Created by Brandon Martin on 10/8/19.
//

#ifndef CURSEN_DROPRESULT_H
#define CURSEN_DROPRESULT_H

#include <array>

struct DropResult
{

    DropResult();

    std::array<int, 4> rowsToClear;
    bool didLose;
    bool nextPiece;
    bool didUpdate;

};


#endif //CURSEN_DROPRESULT_H
