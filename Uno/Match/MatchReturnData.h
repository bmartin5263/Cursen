//
// Created by Brandon Martin on 7/28/19.
//

#ifndef CURSEN_MATCHRETURNDATA_H
#define CURSEN_MATCHRETURNDATA_H

#include <string>

class MatchReturnData
{

public:

    MatchReturnData(std::string message, bool kicked) :
        message(message), kicked(kicked)
    {}

    std::string message;
    bool kicked;

};

#endif //CURSEN_MATCHRETURNDATA_H
