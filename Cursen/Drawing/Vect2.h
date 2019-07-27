//
// Created by Brandon Martin on 3/11/19.
//

#ifndef CURSEN_VECT2D_H
#define CURSEN_VECT2D_H

#include <string>

namespace cursen {

    struct Vect2 {

        Vect2() :
                x(0), y(0)
        {
        }

        explicit Vect2(const int x, const int y) :
                x(x), y(y)
        {
        }

        Vect2(const Vect2& other) :
                x(other.x), y(other.y)
        {
        }

        Vect2& operator = (const Vect2& other) {
            if (this != &other)
            {
                this->x = other.x;
                this->y = other.y;
            }
            return *this;
        }

        Vect2 operator + (Vect2 const &size) const {
            return Vect2(x + size.x, y + size.y);
        }

        Vect2& operator += (const Vect2& size){
            this->x += size.x;
            this->y += size.y;
            return *this;
        }

        Vect2 operator - (Vect2 const &size) const {
            return Vect2(x - size.x, y - size.y);
        }

        Vect2& operator -= (const Vect2& size){
            this->x -= size.x;
            this->y -= size.y;
            return *this;
        }

        Vect2 operator * (Vect2 const &size) const {
            return Vect2(x * size.x, y * size.y);
        }

        Vect2& operator *= (const Vect2& size){
            this->x *= size.x;
            this->y *= size.y;
            return *this;
        }

        Vect2 operator / (Vect2 const &size) const {
            return Vect2(x / size.x, y / size.y);
        }

        Vect2& operator /= (const Vect2& size){
            this->x /= size.x;
            this->y /= size.y;
            return *this;
        }

        bool operator == (const Vect2& other) {
            return x == other.x && y == other.y;
        }

        bool operator != (const Vect2& other) {
            return !(*this == other);
        }

        std::string toString() {
            using namespace std;
            return string("(") + to_string(x) + string(",") + to_string(y) + string(")");
        }

        bool isPositive() const {
            return x >= 0 && y >= 0;
        }

        int x;
        int y;

    };

}

#endif //CURSEN_VECT2D_H
