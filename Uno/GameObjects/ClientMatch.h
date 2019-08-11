//
// Created by Brandon Martin on 7/28/19.
//

#ifndef CURSEN_CLIENTMATCH_H
#define CURSEN_CLIENTMATCH_H

#include "Player.h"
#include "Lobby.h"
#include "Deck.h"

struct ClientMatch : public Serializable
{
    size_t serialize(char* const buffer) const override
    {
        size_t written = 0;

        written += Serializable::Serialize(buffer + written, num_players);
        for (int i = 0; i < num_players; ++i)
        {
            if (players[i].getId() == my_id) written += players[i].serialize(buffer + written);
            else written += players[i].safeSerialize(buffer + written);
        }
        written += pile.serialize(buffer + written);
        written += Serializable::Serialize(buffer + written, current_player_index);
        written += Serializable::Serialize(buffer + written, my_id);
        written += Serializable::Serialize(buffer + written, consecutive_passes);
        written += Serializable::Serialize(buffer + written, deck_size);
        written += Serializable::Serialize(buffer + written, waitingForWildCardColor);
        written += Serializable::Serialize(buffer + written, reversed);

        return written;
    }

    size_t deserialize(const char* const buffer) override
    {
        size_t read = 0;

        read += Serializable::Deserialize(buffer + read, num_players);
        for (int i = 0; i < num_players; ++i)
        {
            read += players[i].deserialize(buffer + read);
        }
        read += pile.deserialize(buffer + read);
        read += Serializable::Deserialize(buffer + read, current_player_index);
        read += Serializable::Deserialize(buffer + read, my_id);
        read += Serializable::Deserialize(buffer + read, consecutive_passes);
        read += Serializable::Deserialize(buffer + read, deck_size);
        read += Serializable::Deserialize(buffer + read, waitingForWildCardColor);
        read += Serializable::Deserialize(buffer + read, reversed);

        return read;
    }

    size_t sizeOf() const override
    {
        return sizeof(ClientMatch);
    }

    Player players[Lobby::MAX_PLAYERS];
    Deck pile;
    int num_players;
    int current_player_index;
    int my_id;
    int consecutive_passes;
    unsigned long deck_size;
    bool waitingForWildCardColor;
    bool reversed;
};

#endif //CURSEN_CLIENTMATCH_H
