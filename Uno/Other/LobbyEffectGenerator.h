//
// Created by Brandon Martin on 5/22/19.
//

#ifndef CURSEN_LOBBYEFFECTGENERATOR_H
#define CURSEN_LOBBYEFFECTGENERATOR_H

#include <vector>
#include <cassert>
#include <Cursen/Drawing/Vect2.h>

enum class Direction
{
    UNINITIALIZED, NORTH, SOUTH, EAST, WEST
};

struct Runner
{

    typedef cursen::Vect2 pair;

    static Direction getOp(Direction d)
    {
        switch (d)
        {

            case Direction::UNINITIALIZED:
                return Direction::UNINITIALIZED;
            case Direction::NORTH:
                return Direction::SOUTH;
            case Direction::SOUTH:
                return Direction::NORTH;
            case Direction::EAST:
                return Direction::WEST;
            case Direction::WEST:
                return Direction::EAST;
        }
    }

    pair coordinates[20];
    Direction last;
    int color;

    Runner(int x, int y, int color)
    {
        pair start(x, y);
        for (int i = 0; i < 20; i++)
        {
            this->coordinates[i] = start;
        }
        this->last = Direction::UNINITIALIZED;
        this->color = color;
    }

    const pair& get(int i)
    {
        return coordinates[i];
    };

    int getColor()
    {
        return color;
    }

    void update(char** maze)
    {

        for (int i = 0; i < 19; i++)
        {
            coordinates[i] = coordinates[i + 1];
        }

        std::vector<Direction> canMove;
        canMove.reserve(4);

        int x = coordinates[19].x;
        int y = coordinates[19].y;
        char current_space = maze[y][x];

        if (x < 69)
        {
            char next = maze[y][x + 1];
            if (next == '1' || next == '2')
            {
                canMove.push_back(Direction::EAST);
            }
        }

        if (x > 0)
        {
            char next = maze[y][x - 1];
            if (next == '1' || next == '2')
            {
                canMove.push_back(Direction::WEST);
            }
        }

        if (current_space != '2')
        {
            if (y < 31)
            {
                char next = maze[y + 1][x];
                if (next == '1')
                {
                    canMove.push_back(Direction::SOUTH);
                }
            }
            if (y > 0)
            {
                char next = maze[y - 1][x];
                if (next == '1')
                {
                    canMove.push_back(Direction::NORTH);
                }
            }
        }

        int val = rand() % (int) canMove.size();

        Direction next = canMove[val];
        while (next == last)
        {
            val = rand() % (int) canMove.size();
            next = canMove[val];
        }

        switch (next)
        {
            case Direction::UNINITIALIZED:
                break;
            case Direction::NORTH:
                y -= 1;
                break;
            case Direction::SOUTH:
                y += 1;
                break;
            case Direction::EAST:
                x += 1;
                break;
            case Direction::WEST:
                x -= 1;
                break;
        }

        coordinates[19] = pair(x, y);

        last = getOp(next);
    }

};

class LobbyEffectGenerator
{

public:

    static const char WALL = '0';


    LobbyEffectGenerator();
    ~LobbyEffectGenerator();

    //char*& operator[](size_t i);

    void update();
    void drawLine(char val, int x, int y, int length);
    void reset();

    std::vector<Runner>& getRunners();

private:

    char** maze;
    std::vector<Runner> runners;

};


#endif //CURSEN_LOBBYEFFECTGENERATOR_H
