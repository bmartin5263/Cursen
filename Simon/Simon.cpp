//
// Created by Brandon Martin on 9/11/19.
//

#include <Uno/Constants.h>
#include "Simon.h"

Simon::Simon() : current(0)
{
}

std::vector<int>& Simon::getOrder()
{
    return order;
}

void Simon::incrementRound()
{
    current = 0;
    order.push_back(Constants::GetRandomNumber());
}

bool Simon::guess(int guess)
{
    return order[current++] == guess;
}

bool Simon::readyForNextRound()
{
    return current >= order.size();
}

int Simon::getLevel()
{
    return order.size();
}

