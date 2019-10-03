//
// Created by Brandon Martin on 9/29/19.
//

#ifndef CURSEN_BLOCK_H
#define CURSEN_BLOCK_H


#include <Cursen/Drawing/Vect2.h>
#include <Cursen/Drawing/ColorPair.h>
#include <array>
#include <ncurses.h>

class Tetromino
{

public:

    typedef std::array<cursen::Vect2, 4> BlockArray;
    typedef chtype** Board;

    /*
     *   XX
     *   XX
     */
    static const Tetromino O_0;

    /*
     *   X
     *   X
     *   XX
     */
    static const Tetromino L_0;
    static const Tetromino L_1;
    static const Tetromino L_2;
    static const Tetromino L_3;

    /*
     *    X
     *    X
     *   XX
     */
    static const Tetromino J_0;
    static const Tetromino J_1;
    static const Tetromino J_2;
    static const Tetromino J_3;

    static const Tetromino T_0;
    static const Tetromino T_1;
    static const Tetromino T_2;
    static const Tetromino T_3;

    static const Tetromino S_0;
    static const Tetromino S_1;

    static const Tetromino Z_0;
    static const Tetromino Z_1;

    static const Tetromino I_0;
    static const Tetromino I_1;

    static const cursen::ColorPair YELLOW_BLOCK;
    static const cursen::ColorPair CYAN_BLOCK;
    static const cursen::ColorPair BLUE_BLOCK;
    static const cursen::ColorPair RED_BLOCK;
    static const cursen::ColorPair GREEN_BLOCK;
    static const cursen::ColorPair PURPLE_BLOCK;
    static const cursen::ColorPair ORANGE_BLOCK;

    static void InitializeGraphics();

    const void placeOnto(Board& board, cursen::Vect2 position) const;
    const void removeFrom(Board& board, cursen::Vect2 position, chtype clear_value) const;

    const BlockArray& body() const;
    const Tetromino& rotateLeft() const;
    const Tetromino& rotateRight() const;

    const chtype getGraphic() const;


private:

    Tetromino(const BlockArray& blocks, const Tetromino& left, const Tetromino& right);
    Tetromino(const Tetromino& other) = delete;
    Tetromino& operator = (const Tetromino& other) = delete;
    ~Tetromino() = default;

    void setGraphic(chtype graphic) const;

    const BlockArray blocks;
    const Tetromino& left_rotation;
    const Tetromino& right_rotation;
    mutable chtype graphic;

};


#endif //CURSEN_BLOCK_H
