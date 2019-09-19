//
// Created by Brandon Martin on 9/11/19.
//

#ifndef CURSEN_SIMON_H
#define CURSEN_SIMON_H

#include <vector>

class Simon
{

public:

    Simon();

    std::vector<int>& getOrder();
    void incrementRound();
    bool guess(int guess);
    bool readyForNextRound();

    int getLevel();

private:

    int current;
    std::vector<int> order;

};


#endif //CURSEN_SIMON_H
