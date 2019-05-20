//
// Created by Brandon Martin on 5/20/19.
//

#ifndef CURSEN_SENDTYPE_H
#define CURSEN_SENDTYPE_H

// Convert to bit flags later
enum class SendType {

    Uninitialized = 1,
    Local = 2,
    Network = 4,
    Both = 8

};

#endif //CURSEN_SENDTYPE_H
