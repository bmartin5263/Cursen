//
// Created by Brandon Martin on 5/20/19.
//

#ifndef CURSEN_MESSAGETYPES_H
#define CURSEN_MESSAGETYPES_H

enum class MessageType {

    Uninitialized,
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
    MatchConnectionSevered,
    InputDealCards,
    DealCards,
    InputBeginGame,
    BeginGame,
    InputDrawCard,
    DrawCard,
    InputPlayCard,
    PlayCard,
    InputWildColorChange,
    WildColorChange,
    InputEnterMatch,
    EnterMatch,
    RequestMatchData,
    ClientMatchUpdate,
    IllegalAction,
    InputPass,
    PassTurn,
    InputGameOver,
    GameOver,
    InputEndGame,
    EndGame,
};

#endif //CURSEN_MESSAGETYPES_H
