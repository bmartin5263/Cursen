//
// Created by Brandon Martin on 9/29/19.
//

#include <Cursen/Drawing/ColorPair.h>
#include "Tetromino.h"

using namespace cursen;

const Tetromino Tetromino::O_0({Vect2(0,0), Vect2(0,1), Vect2(1,0), Vect2(1,1)}, Tetromino::O_0, Tetromino::O_0);

const Tetromino Tetromino::L_0({Vect2(0,0), Vect2(0,1), Vect2(1,1), Vect2(2,1)}, Tetromino::L_3, Tetromino::L_1);
const Tetromino Tetromino::L_1({Vect2(0,0), Vect2(0,1), Vect2(0,2), Vect2(1,0)}, Tetromino::L_0, Tetromino::L_2);
const Tetromino Tetromino::L_2({Vect2(0,0), Vect2(1,0), Vect2(2,0), Vect2(2,1)}, Tetromino::L_1, Tetromino::L_3);
const Tetromino Tetromino::L_3({Vect2(0,2), Vect2(1,2), Vect2(1,1), Vect2(1,0)}, Tetromino::L_2, Tetromino::L_0);

const Tetromino Tetromino::J_0({Vect2(0,1), Vect2(1,1), Vect2(2,0), Vect2(2,1)}, Tetromino::J_3, Tetromino::J_1);
const Tetromino Tetromino::J_1({Vect2(0,0), Vect2(0,1), Vect2(0,2), Vect2(1,2)}, Tetromino::J_0, Tetromino::J_2);
const Tetromino Tetromino::J_2({Vect2(0,0), Vect2(0,1), Vect2(1,0), Vect2(2,0)}, Tetromino::J_1, Tetromino::J_3);
const Tetromino Tetromino::J_3({Vect2(0,0), Vect2(1,0), Vect2(1,1), Vect2(1,2)}, Tetromino::J_2, Tetromino::J_0);

const Tetromino Tetromino::T_0({Vect2(0,0), Vect2(1,0), Vect2(2,0), Vect2(1,1)}, Tetromino::T_3, Tetromino::T_1);
const Tetromino Tetromino::T_1({Vect2(1,0), Vect2(2,0), Vect2(2,1), Vect2(2,-1)}, Tetromino::T_0, Tetromino::T_2);
const Tetromino Tetromino::T_2({Vect2(0,1), Vect2(1,1), Vect2(1,0), Vect2(2,1)}, Tetromino::T_1, Tetromino::T_3);
const Tetromino Tetromino::T_3({Vect2(0,0), Vect2(0,1), Vect2(1,0), Vect2(0,-1)}, Tetromino::T_2, Tetromino::T_0);

const Tetromino Tetromino::S_0({Vect2(0,0), Vect2(1,0), Vect2(1,1), Vect2(2,1)}, Tetromino::S_1, Tetromino::S_1);
const Tetromino Tetromino::S_1({Vect2(0,1), Vect2(0,2), Vect2(1,1), Vect2(1,2)}, Tetromino::S_0, Tetromino::S_0);

const Tetromino Tetromino::Z_0({Vect2(0,1), Vect2(1,1), Vect2(1,0), Vect2(2,0)}, Tetromino::Z_1, Tetromino::Z_1);
const Tetromino Tetromino::Z_1({Vect2(0,0), Vect2(0,1), Vect2(1,1), Vect2(1,2)}, Tetromino::Z_0, Tetromino::Z_0);

const Tetromino Tetromino::I_0({Vect2(0,0), Vect2(1,0), Vect2(2,0), Vect2(3,0)}, Tetromino::I_1, Tetromino::I_1);
const Tetromino Tetromino::I_1({Vect2(2,0), Vect2(2,1), Vect2(2,2), Vect2(2,3)}, Tetromino::I_0, Tetromino::I_0);

const ColorPair Tetromino::YELLOW_BLOCK(Color::BLACK, Color::YELLOW);
const ColorPair Tetromino::BLUE_BLOCK(Color::BLACK, Color(39));
const ColorPair Tetromino::GREEN_BLOCK(Color::BLACK, Color::GREEN);
const ColorPair Tetromino::PURPLE_BLOCK(Color::BLACK, Color::LAVENDER);
const ColorPair Tetromino::ORANGE_BLOCK(Color::BLACK, Color::ORANGE);
const ColorPair Tetromino::CYAN_BLOCK(Color::BLACK, Color::BLUE);
const ColorPair Tetromino::RED_BLOCK(Color::BLACK, Color(203));


void Tetromino::InitializeGraphics()
{
    /*
     * Graphics have to be initialized non-statically separately since they rely on
     * Cursen's color capabilities, which don't get initialized until runtime.
     */

    O_0.setGraphic(' ' | ColorPair(Color::BLACK, Color::YELLOW));

    L_0.setGraphic(' ' | ORANGE_BLOCK);
    L_1.setGraphic(' ' | ORANGE_BLOCK);
    L_2.setGraphic(' ' | ORANGE_BLOCK);
    L_3.setGraphic(' ' | ORANGE_BLOCK);

    J_0.setGraphic(' ' | BLUE_BLOCK);
    J_1.setGraphic(' ' | BLUE_BLOCK);
    J_2.setGraphic(' ' | BLUE_BLOCK);
    J_3.setGraphic(' ' | BLUE_BLOCK);

    T_0.setGraphic(' ' | CYAN_BLOCK);
    T_1.setGraphic(' ' | CYAN_BLOCK);
    T_2.setGraphic(' ' | CYAN_BLOCK);
    T_3.setGraphic(' ' | CYAN_BLOCK);

    S_0.setGraphic(' ' | PURPLE_BLOCK);
    S_1.setGraphic(' ' | PURPLE_BLOCK);

    Z_0.setGraphic(' ' | GREEN_BLOCK);
    Z_1.setGraphic(' ' | GREEN_BLOCK);

    I_0.setGraphic(' ' | RED_BLOCK);
    I_1.setGraphic(' ' | RED_BLOCK);
}

Tetromino::Tetromino(const BlockArray& blocks, const Tetromino& left, const Tetromino& right) :
    blocks(blocks), left_rotation(left), right_rotation(right), graphic('?')
{

}

const Tetromino::BlockArray& Tetromino::body() const
{
    return blocks;
}

const Tetromino& Tetromino::rotateLeft() const
{
    return left_rotation;
}

const Tetromino& Tetromino::rotateRight() const
{
    return right_rotation;
}

const chtype Tetromino::getGraphic() const
{
    return graphic;
}

void Tetromino::setGraphic(chtype graphic) const
{
    this->graphic = graphic;
}
