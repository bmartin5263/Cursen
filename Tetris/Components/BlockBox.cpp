//
// Created by Brandon Martin on 10/10/19.
//

#include "BlockBox.h"

using namespace cursen;

BlockBox::BlockBox() : field(Vect2(5,2))
{

}

void BlockBox::initialize()
{
    border.initialize();
    border.setSize(Vect2(12, 4));
    border.setPosition(Vect2(0,0));
    addRelative(border);

    title.initialize();
    title.setPosition(Vect2(1,0));
    title.drawOnTopOf(border);
    title.setForeground(Color::YELLOW);
    addRelative(title);

    field.initialize();
    field.setPosition(border.getPosition() + Vect2(1,1));
    addRelative(field);
}

void BlockBox::setTetromino(const Tetromino& tetromino)
{
    field.setTetromino(tetromino, Vect2(1,0));
}

void BlockBox::setText(const std::string& text)
{
    title.setText("[ " + text + " ]");
}
