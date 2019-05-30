//
// Created by Brandon Martin on 5/29/19.
//

#ifndef CURSEN_HANDLE_H
#define CURSEN_HANDLE_H

#define HANDLE_VARIABLE			Handle handle;

#define HANDLE_CHECK_BEGIN		HandleStatus status = Handle::IsValid(handle);\
								if (status == HandleStatus::Success) {

#define HANDLE_CHECK_END		} return status;

#define HANDLE_INVALIDATE       Handle::InvalidateHandle(handle);

enum class HandleStatus {
    Success, Invalid, Error, InsufficientSpace
};

class Handle
{
public:

    Handle();
    ~Handle();

    Handle(const Handle &) = delete;
    const Handle & operator = (const Handle &) = delete;

    unsigned int getIndex() const;
    unsigned int getId() const;

    static HandleStatus IsValid(Handle& handle);
    static HandleStatus Invalidate(Handle& handle);

private:

    unsigned int id;
    unsigned int index;

};


#endif //CURSEN_HANDLE_H
