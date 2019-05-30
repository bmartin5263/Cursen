//
// Created by Brandon Martin on 5/29/19.
//

#include <cassert>
#include "HandleManager.h"

HandleManager::HandleManager()
{
    this->nextId = HANDLE_STARTING_ID;	// Where we will start with the ids
    for (int i = 0; i < HANDLE_TABLE_SIZE; i++)
    {
        // Invalidate Entire Table
        this->handle_table[i].id = HANDLE_INVALID_STATE;
    }
}

HandleManager::~HandleManager()
{
    this->nextId = HANDLE_STARTING_ID;
    for (int i = 0; i < HANDLE_TABLE_SIZE; i++)
    {
        // Invalidate Entire Table Again
        this->handle_table[i].id = HANDLE_INVALID_STATE;
    }
}

unsigned int HandleManager::privGetNewID()
{
    return this->nextId++;
}


HandleStatus HandleManager::InvalidateHandle(Handle &handle)
{
    HandleManager *pMan = HandleManager::privInstance();
    assert(pMan);

    HandleStatus status = HandleStatus::Invalid;

    status = HandleManager::IsValid(handle);
    //assert(status == HandleStatus::SUCCESS);

    pMan->handle_table[handle.getIndex()].id = HANDLE_INVALID_STATE;

    return status;
}


HandleStatus HandleManager::IsValid(Handle &handle)
{
    HandleManager *pMan = HandleManager::privInstance();
    assert(pMan);

    HandleStatus status = HandleStatus::Error;

    if (handle.getIndex() < HANDLE_TABLE_SIZE)
    {
        if (pMan->handle_table[handle.getIndex()].id.load() == handle.getId())
        {
            status = HandleStatus::Success;
        }
        else
        {
            status = HandleStatus::Invalid;
        }
    }
    else
    {
        status = HandleStatus::Invalid;
    }

    // trap for Debug
    // assert(status == HandleStatus::Success);

    return status;
}


HandleStatus HandleManager::ActivateHandle(unsigned int &id, unsigned int &index)
{
    HandleManager *pMan = HandleManager::privInstance();
    assert(pMan);

    HandleStatus status;

    if (pMan->privFindNextAvailable(index))
    {
        status = HandleStatus::Success;

        // Set it
        id = pMan->privGetNewID();
        pMan->handle_table[index].id = id;
    }
    else
    {
        status = HandleStatus::InsufficientSpace;
    }

    // trap for Debug
    assert(status == HandleStatus::Success);

    return status;
}

bool HandleManager::privFindNextAvailable(unsigned int &index)
{
    bool status = false;

    for (unsigned int i = 0; i < HANDLE_TABLE_SIZE; i++)
    {
        if (this->handle_table[i].id.load() == HANDLE_INVALID_STATE)
        {
            // found one
            index = i;
            status = true;
            break;
        }
    }

    return status;
}

HandleStatus HandleManager::privIsHandleValid(Handle &handle)
{
    HandleStatus status = HandleStatus::Error;

    if (this->handle_table[handle.getIndex()].id.load() == handle.getId())
    {
        status = HandleStatus::Success;
    }
    else
    {
        status = HandleStatus::Invalid;
    }

    return status;
}

HandleStatus HandleManager::privIsHandleAndRangeValid(Handle &handle)
{
    HandleStatus status = HandleStatus::Error;

    if (handle.getIndex() < HANDLE_TABLE_SIZE)
    {
        if (this->handle_table[handle.getIndex()].id.load() == handle.getId())
        {
            status = HandleStatus::Success;
        }
        else
        {
            status = HandleStatus::Invalid;
        }
    }
    else
    {
        status = HandleStatus::Invalid;
    }

    return status;
}

HandleManager *HandleManager::privInstance()
{
    // Here's the singleton
    static HandleManager instance;

    return &instance;
}