//
// Created by Brandon Martin on 5/20/19.
//

#include <cassert>
#include <Uno/Match/Messages/InputDealCards.h>
#include <Uno/Match/Messages/InputBeginGame.h>
#include <Uno/Match/Messages/InputDrawCard.h>
#include <Uno/Match/Messages/InputPlayCard.h>
#include <Uno/Match/Messages/InputWildColorChange.h>
#include <Uno/Match/Messages/RequestMatchData.h>
#include <Uno/Match/Messages/MatchConnectionSevered.h>
#include <Uno/Match/Messages/InputPass.h>
#include <Uno/Match/Messages/InputGameOver.h>
#include <Uno/Match/Messages/EndGame.h>
#include <Uno/Match/Messages/InputEndGame.h>

#include "DataMessage.h"
#include "ChangeColor.h"
#include "CloseRoom.h"
#include "InputAddAi.h"
#include "InputChangeColor.h"
#include "InputChat.h"
#include "InputKick.h"
#include "InputCloseRoom.h"
#include "KickPlayer.h"
#include "LobbyUpdate.h"
#include "PushChatLog.h"
#include "RequestJoinLobby.h"
#include "InputSearch.h"
#include "DisconnectFromHost.h"
#include "ConnectionSevered.h"
#include "InputEnterMatch.h"
#include "AddPlayer.h"
#include "UpdatePlayer.h"

DataMessage* DataMessage::Parse(MessageType type)
{
    DataMessage* msg = nullptr;
    switch (type)
    {
        case MessageType::Uninitialized:
            assert(false);
            break;
        case MessageType::InputChangeColor:
            msg = new InputChangeColor;
            break;
        case MessageType::ChangeColor:
            msg = new ChangeColor;
            break;
        case MessageType::InputChat:
            msg = new InputChat;
            break;
        case MessageType::PushChatLog:
            msg = new PushChatLog;
            break;
        case MessageType::InputAddAi:
            msg = new InputAddAi;
            break;
        case MessageType::InputKick:
            msg = new InputKick;
            break;
        case MessageType::KickPlayer:
            msg = new KickPlayer;
            break;
        case MessageType::InputClose:
            msg = new InputCloseRoom;
            break;
        case MessageType::CloseRoom:
            msg = new CloseRoom;
            break;
        case MessageType::RequestJoinLobby:
            msg = new RequestJoinLobby;
            break;
        case MessageType::LobbyUpdate:
            msg = new LobbyUpdate;
            break;
        case MessageType::InputSearch:
            msg = new InputSearch;
            break;
        case MessageType::StartSearch:
            msg = new StartSearch;
            break;
        case MessageType::StopSearch:
            msg = new StopSearch;
            break;
        case MessageType::RequestLeaveLobby:
            assert(false);
            break;
        case MessageType::DisconnectFromHost:
            msg = new DisconnectFromHost;
            break;
        case MessageType::ConnectionSevered:
            msg = new ConnectionSevered;
            break;
        case MessageType::InputDealCards:
            msg = new InputDealCards;
            break;
        case MessageType::DealCards:
            msg = new DealCards;
            break;
        case MessageType::InputBeginGame:
            msg = new InputBeginGame;
            break;
        case MessageType::BeginGame:
            msg = new BeginGame;
            break;
        case MessageType::InputDrawCard:
            msg = new InputDrawCard;
            break;
        case MessageType::DrawCard:
            msg = new DrawCard;
            break;
        case MessageType::InputPlayCard:
            msg = new InputPlayCard;
            break;
        case MessageType::PlayCard:
            msg = new PlayCard;
            break;
        case MessageType::InputWildColorChange:
            msg = new InputWildColorChange;
            break;
        case MessageType::WildColorChange:
            msg = new WildColorChange;
            break;
        case MessageType::InputEnterMatch:
            msg = new InputEnterMatch;
            break;
        case MessageType::EnterMatch:
            msg = new EnterMatch;
            break;
        case MessageType::RequestMatchData:
            msg = new RequestMatchData;
            break;
        case MessageType::ClientMatchUpdate:
            msg = new ClientMatchUpdate;
            break;
        case MessageType::MatchConnectionSevered:
            msg = new MatchConnectionSevered;
            break;
        case MessageType::IllegalAction:
            msg = new IllegalAction;
            break;
        case MessageType::InputPass:
            msg = new InputPass;
            break;
        case MessageType::PassTurn:
            msg = new PassTurn;
            break;
        case MessageType::InputGameOver:
            msg = new InputGameOver;
            break;
        case MessageType::GameOver:
            msg = new GameOver;
            break;
        case MessageType::InputEndGame:
            msg = new InputEndGame;
            break;
        case MessageType::EndGame:
            msg = new EndGame;
            break;
        case MessageType::AddPlayer:
            msg = new AddPlayer;
            break;
        case MessageType::UpdatePlayer:
            msg = new UpdatePlayer;
            break;
    }
    assert(msg != nullptr);
    return msg;
}

size_t DataMessage::sizeOf() const
{
    return sizeof(DataMessage);
}

size_t DataMessage::serialize(char* const buffer) const
{
    size_t written = 0;

    written += Serializable::Serialize(buffer + written, (int)sendType);
    written += Serializable::Serialize(buffer + written, (int)recipientType);
    written += Serializable::Serialize(buffer + written, senderId);
    written += Serializable::Serialize(buffer + written, recipientId);
    written += Serializable::Serialize(buffer + written, allow_loopback);

    return written;
}

size_t DataMessage::deserialize(const char* const buffer)
{
    size_t read = 0;

    int raw_sendType;
    int raw_recipientType;

    read += Serializable::Deserialize(buffer + read, raw_sendType);
    read += Serializable::Deserialize(buffer + read, raw_recipientType);
    read += Serializable::Deserialize(buffer + read, senderId);
    read += Serializable::Deserialize(buffer + read, recipientId);
    read += Serializable::Deserialize(buffer + read, allow_loopback);

    sendType = (SendType)raw_sendType;
    recipientType = (RecipientType)raw_recipientType;

    return read;
}