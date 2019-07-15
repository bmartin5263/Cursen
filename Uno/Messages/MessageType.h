//
// Created by Brandon Martin on 5/20/19.
//

#ifndef CURSEN_MESSAGETYPES_H
#define CURSEN_MESSAGETYPES_H

enum class MessageType {

    Uninitialized,
    ChangeContextLobby,     // Tells Player that we are now listening for lobby messages
    ChangeContextMatch,     // Tells Player that we are now listening for match messages
    InputChangeColor,
    ChangeColor,
    InputChat,
    PushChatLog,
    AddAI,
    InputAddAi,
    InputKick,
    KickPlayer,
    InputClose,
    CloseRoom,
    RequestJoinLobby,
    RequestLeaveLobby,
    AddPlayer,
    LobbyUpdate,
    InputSearch,
    StartSearch,
    StopSearch,
    DisconnectFromHost,
    ConnectionSevered,
    InputEnter,
    DealCards

};

#endif //CURSEN_MESSAGETYPES_H
