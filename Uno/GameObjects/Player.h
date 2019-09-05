//
// Created by Brandon Martin on 4/11/19.
//

#ifndef CURSEN_PLAYER_H
#define CURSEN_PLAYER_H

#include <string>

#include "Uno/Messages/Serializable.h"
#include "Cursen/Drawing/Color.h"
#include "PlayerColor.h"
#include "Hand.h"

class Player : public Serializable {

public:

    Player();
    Player(const std::string& name, const PlayerColor& color, int id, bool ai, bool dummy);

    void setName(const std::string& name);
    std::string getName() const;

    void addPoints(int points);
    int getPoints() const;

    void setColor(const PlayerColor& color);
    PlayerColor getColor() const;

    int getId() const;
    void clear();

    bool isAI() const;
    bool isDummy() const;
    bool hasPlayableCard(const Card& card);
    int getPlayableCardIndex(const Card& card);

    CardColor getWildColor();

    void addForceDraws(int count);
    void decrementForceDraws();
    void clearForceDraws();
    int getForceDraws();

    static const std::string GetComputerName();
    static cursen::Color ConvertColor(const PlayerColor& color);
    static cursen::Color ConvertColorLight(const PlayerColor& color);

    size_t serialize(char* const buffer) const override;
    size_t deserialize(const char* const buffer) override;
    size_t safeSerialize(char* const buffer, bool safe_serialize_hand) const;

    size_t sizeOf() const override;

    size_t getHandSize() const;
    Hand& getHand();

private:

    static const std::string COMP_NAMES[];

    std::string name;
    PlayerColor color;
    Hand hand;
    int points;
    int id;
    int force_draws;
    bool ai;
    bool dummy;

};


#endif //CURSEN_PLAYER_H
