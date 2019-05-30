//
// Created by Brandon Martin on 5/29/19.
//

#include <assert.h>

#include "Handle.h"
#include "Cursen/Drawing/CursesManager.h"
#include "HandleManager.h"

Handle::Handle()
{
    HandleStatus status = HandleManager::ActivateHandle(this->id, this->index);
    assert(status == HandleStatus::Success);
    cursen::CursesManager::Flash();
}

Handle::~Handle()
{
    HandleManager::InvalidateHandle(*this);
}

unsigned int Handle::getId() const
{
    return this->id;
}

unsigned int Handle::getIndex() const
{
    return this->index;
}

HandleStatus Handle::IsValid(Handle &handle)
{
    return HandleManager::IsValid(handle);
}

HandleStatus Handle::Invalidate(Handle &handle)
{
    return HandleManager::InvalidateHandle(handle);
}