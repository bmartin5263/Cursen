//
// Created by Brandon Martin on 5/22/19.
//

#ifndef CURSEN_LOBBYEFFECTGENERATOR_H
#define CURSEN_LOBBYEFFECTGENERATOR_H

#include <vector>
#include <unordered_set>
#include <cassert>
#include <Cursen/Drawing/Vect2.h>
#include "Cursen/Events/EventManager.h"

enum class Direction
{
    UNINITIALIZED, NORTH, SOUTH, EAST, WEST
};

class Runners
{
    int colors[4];
    int next_to_go[4];
    cursen::Vect2 coordinates[4][20];
    Direction last[4];
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

    int color;
    int next_to_go;
    pair coordinates[20];
    Direction last;
    std::unordered_set<Direction, cursen::EnumClassHash> canMove;

    Runner() = default;

    void setColor(int color)
    {
        this->color = color;
    }

    void reset(int x, int y)
    {
        for (int i = 0; i < 20; i++)
        {
            coordinates[i] = pair(x,y);
        }
        this->last = Direction::UNINITIALIZED;
        this->next_to_go = 0;
    }

    const pair& get(int i)
    {
        return coordinates[i];
    };

    constexpr int getColor() const
    {
        return color;
    }

    void update(char** maze)
    {

        //for (int i = 0; i < 19; i++)
        //{
        //    coordinates[i] = coordinates[i + 1];
        //}

        canMove.clear();
        canMove.reserve(4);

        //int x = coordinates[19].x;
        //int y = coordinates[19].y;
        pair prev = next_to_go > 0 ? coordinates[next_to_go-1] : coordinates[19];
        int x = prev.x;
        int y = prev.y;
        char current_space = maze[y][x];

        if (x < 69 && Direction::EAST != last)
        {
            char next = maze[y][x + 1];
            if (next == '1' || next == '2')
            {
                canMove.insert(Direction::EAST);
            }
        }

        if (x > 0 && Direction::WEST != last)
        {
            char next = maze[y][x - 1];
            if (next == '1' || next == '2')
            {
                canMove.insert(Direction::WEST);
            }
        }

        if (current_space != '2')
        {
            if (y < 31 && maze[y + 1][x] == '1' && Direction::SOUTH != last)
            {
                canMove.insert(Direction::SOUTH);
            }
            if (y > 0 && maze[y - 1][x] == '1' && Direction::NORTH != last)
            {
                canMove.insert(Direction::NORTH);
            }
        }

        auto it = canMove.begin();
        int val = rand() % (int) canMove.size();
        std::advance(it, val);
        Direction next = *it;

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

        coordinates[next_to_go++] = pair(x, y);
        if (next_to_go >= 20) next_to_go = 0;

        switch (next)
        {

            case Direction::UNINITIALIZED:
                last =  Direction::UNINITIALIZED;
                break;
            case Direction::NORTH:
                last =  Direction::SOUTH;
                break;
            case Direction::SOUTH:
                last =  Direction::NORTH;
                break;
            case Direction::EAST:
                last =  Direction::WEST;
                break;
            case Direction::WEST:
                last =  Direction::EAST;
                break;
        }
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

    Runner*& getRunners();

private:

    //Runner* runners_alloc;
    char** maze;
    Runner* runners;

};


#endif //CURSEN_LOBBYEFFECTGENERATOR_H
