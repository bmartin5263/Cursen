//
// Created by Brandon Martin on 3/12/19.
//

#ifndef CURSEN_ARROWMAP_H
#define CURSEN_ARROWMAP_H

class VisualComponent;

namespace cursen {

    struct ArrowMap {

        ArrowMap() {
            this->left = nullptr;
            this->up = nullptr;
            this->down = nullptr;
            this->right = nullptr;
        }

        ArrowMap(const ArrowMap& other) {
            //CursesManager::Beep();
            this->left = other.left;
            this->down = other.down;
            this->right = other.right;
            this->up = other.up;
        }

        ArrowMap& operator = (const ArrowMap& other) {
            this->left = other.left;
            this->down = other.down;
            this->right = other.right;
            this->up = other.up;

            return *this;
        }

        ArrowMap(VisualComponent* left, VisualComponent* up, VisualComponent* right, VisualComponent* down) {
            this->left = left;
            this->up = up;
            this->down = down;
            this->right = right;
        }

        VisualComponent* left;
        VisualComponent* up;
        VisualComponent* right;
        VisualComponent* down;

    };

}

#endif //CURSEN_ARROWMAP_H
