//
// Created by Brandon Martin on 9/29/19.
//

#include "BlockGenerator.h"

const Tetromino* BlockGenerator::TETROMINOS[7] {
    &Tetromino::I_0,
    &Tetromino::O_0,
    &Tetromino::S_0,
    &Tetromino::Z_0,
    &Tetromino::T_0,
    &Tetromino::L_0,
    &Tetromino::J_0
};

BlockGenerator::BlockGenerator() :
    generator(std::random_device()()), distribution(0,6)
{
    next_blocks[0] = TETROMINOS[distribution(generator)];
    next_blocks[1] = TETROMINOS[distribution(generator)];
}

BlockGenerator::BlockGenerator(unsigned int seed) :
        generator(std::random_device()()), distribution(0,6)
{
    generator.seed(seed);
    next_blocks[0] = TETROMINOS[distribution(generator)];
    next_blocks[1] = TETROMINOS[distribution(generator)];
}

const Tetromino* BlockGenerator::next()
{
    const Tetromino* return_block = next_blocks[0];
    next_blocks[0] = next_blocks[1];
    next_blocks[1] = TETROMINOS[distribution(generator)];
    return return_block;
}

const Tetromino* BlockGenerator::peekNext()
{
    return next_blocks[0];
}

const Tetromino* BlockGenerator::peekAfter()
{
    return next_blocks[1];
}
