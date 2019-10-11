//
// Created by Brandon Martin on 10/10/19.
//

#ifndef CURSEN_BLOCKBOX_H
#define CURSEN_BLOCKBOX_H


#include <Cursen/Components/AggregateComponent.h>
#include <Cursen/Components/Box.h>
#include <Cursen/Components/Label.h>
#include "TetrominoField.h"

class BlockBox : public cursen::AggregateComponent
{

public:

    BlockBox();
    void initialize() override;

    void setTetromino(const Tetromino& tetromino);
    void setText(const std::string& text) override;

private:

    cursen::Label title;
    cursen::Box border;
    TetrominoField field;

};


#endif //CURSEN_BLOCKBOX_H
