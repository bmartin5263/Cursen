//
// Created by Brandon Martin on 9/29/19.
//

#ifndef CURSEN_BLOCKGENERATOR_H
#define CURSEN_BLOCKGENERATOR_H


#include <Tetris/Components/Tetromino.h>
#include <random>

class BlockGenerator
{

public:

    static const Tetromino* TETROMINOS[7];

    BlockGenerator();
    BlockGenerator(const BlockGenerator& other) = default;

    const Tetromino* next();

private:

    std::random_device rd;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution;

};


#endif //CURSEN_BLOCKGENERATOR_H
