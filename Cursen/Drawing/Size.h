//
// Created by Brandon Martin on 3/11/19.
//

#ifndef CURSEN_VECT2D_H
#define CURSEN_VECT2D_H

#include <string>

namespace cursen {

    struct Size {

        Size() :
                x(0), y(0)
        {
        }

        Size(int x, int y) :
                x(x), y(y)
        {
        }

        Size(const Size& other) :
                x(other.x), y(other.y)
        {
        }

        Size& operator = (const Size& other) {
            this->x = other.x;
            this->y = other.y;
            return *this;
        }

        Size operator + (Size const &size) const {
            return Size(x + size.x, y + size.y);
        }

        Size& operator += (const Size& size){
            this->x += size.x;
            this->y += size.y;
            return *this;
        }

        Size operator - (Size const &size) const {
            return Size(x - size.x, y - size.y);
        }

        Size& operator -= (const Size& size){
            this->x -= size.x;
            this->y -= size.y;
            return *this;
        }

        Size operator * (Size const &size) const {
            return Size(x * size.x, y * size.y);
        }

        Size& operator *= (const Size& size){
            this->x *= size.x;
            this->y *= size.y;
            return *this;
        }

        Size operator / (Size const &size) const {
            return Size(x / size.x, y / size.y);
        }

        Size& operator /= (const Size& size){
            this->x /= size.x;
            this->y /= size.y;
            return *this;
        }

        bool operator == (const Size& other) {
            return x == other.x && y == other.y;
        }

        bool operator != (const Size& other) {
            return x != other.x && y != other.y;
        }

        std::string toString() {
            using namespace std;
            return string("(") + to_string(x) + string(",") + to_string(y) + string(")");
        }

        int x;
        int y;

    };

}

#endif //CURSEN_VECT2D_H
