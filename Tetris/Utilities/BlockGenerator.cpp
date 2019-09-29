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
    generator(rd()), distribution(0,6)
{

}

const Tetromino* BlockGenerator::next()
{
    return TETROMINOS[distribution(generator)];
}
