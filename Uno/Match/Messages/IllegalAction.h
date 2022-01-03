//
// Created by Brandon Martin on 8/11/19.
//

#ifndef CURSEN_ILLEGALACTION_H
#define CURSEN_ILLEGALACTION_H

#include <Uno/Data/DataManager.h>
#include <Uno/Forms/MatchForm.h>
#include "Uno/Messages/DataMessage.h"
#include "Uno/GameObjects/Match.h"

class IllegalAction : public DataMessage
{
public:

    IllegalAction() = default;
    IllegalAction(const std::string& msg) :
            msg(msg)
    {}

    MessageType getType() override
    {
        return MessageType::IllegalAction;
    }

    Context getContext() override
    {
        return Context::Match;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

        MatchForm* matchForm = GetCurrentForm<MatchForm>();
        cursen::TerminalManager::Beep();
        matchForm->setConsoleWarning(msg);

        CONTEXT_END
    }

    DataMessage* clone() override
    {
        return new IllegalAction(*this);
    }

    size_t serialize(char* const buffer) const override
    {
        size_t written =  DataMessage::serialize(buffer);

        written += Serializable::Serialize(buffer + written, msg);

        return written;
    }

    size_t deserialize(const char* const buffer) override
    {
        size_t read = DataMessage::deserialize(buffer);

        read += Serializable::Deserialize(buffer + read, msg);

        return read;
    }

private:

    std::string msg;

};

#endif //CURSEN_ILLEGALACTION_H
