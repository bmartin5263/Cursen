//
// Created by Brandon Martin on 5/29/19.
//

#ifndef CURSEN_HANDLEMANAGER_H
#define CURSEN_HANDLEMANAGER_H

#include <atomic>
#include <thread>

#include "Handle.h"

/**
 * Special Thanks to Edward Keenan for Demoing this Handle System in our Multithreaded
 * Audio Engine class.
 */

class HandleManager
{

private:

    static const unsigned int HANDLE_TABLE_SIZE = 1024;
    static const unsigned int HANDLE_INVALID_STATE = 0x0;
    static const unsigned int HANDLE_STARTING_ID = 0xAAAA0000;

    class HandleEntry
    {
    public:

        HandleEntry() = default;
        HandleEntry(const HandleEntry &) = delete;
        HandleEntry & operator = (const HandleEntry &) = delete;
        ~HandleEntry() = default;

    public:
        std::atomic_uint id;
        std::mutex mtx;
    };

public:

    static HandleStatus ActivateHandle(unsigned int &id, unsigned int &index);
    static HandleStatus InvalidateHandle(Handle &handle);
    static HandleStatus IsValid(Handle &handle);

private:

    HandleManager();
    HandleManager(const HandleManager &) = delete;
    const HandleManager & operator = (const HandleManager &) = delete;
    ~HandleManager();

    static HandleManager *privInstance();

    unsigned int privGetNewID();
    bool privFindNextAvailable(unsigned int &index);
    HandleStatus privIsHandleValid(Handle &handle);
    HandleStatus privIsHandleAndRangeValid(Handle &handle);

    HandleEntry handle_table[HANDLE_TABLE_SIZE];
    unsigned int nextId;

};


#endif //CURSEN_HANDLEMANAGER_H
