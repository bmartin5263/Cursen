//
// Created by Brandon Martin on 5/22/19.
//

#ifndef CURSEN_LOBBYEFFECTGENERATOR_H
#define CURSEN_LOBBYEFFECTGENERATOR_H

#include <vector>
#include <cassert>

enum class Direction
{
    UNINITIALIZED, NORTH, SOUTH, EAST, WEST
};

struct Runner
{

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

    typedef std::pair<int, int> pair;

    std::pair<int, int>* coordinates;
    int size;
    Direction last;

    Runner(int x, int y, int size) :
            size(size)
    {
        pair start(x, y);
        this->coordinates = new pair[size];
        for (int i = 0; i < size; i++)
        {
            this->coordinates[i] = start;
        }
        this->last = Direction::UNINITIALIZED;
    }

    Runner(const Runner& other)
    {
        this->size = other.size;
        this->coordinates = new pair[size];
        for (int i = 0; i < size; i++)
        {
            this->coordinates[i] = other.coordinates[i];
        }
        this->last = other.last;
    }

    Runner& operator = (const Runner& other) {
        if (&other != this) {
            this->size = other.size;

            delete[] coordinates;
            this->coordinates = new pair[size];
            for (int i = 0; i < size; i++)
            {
                this->coordinates[i] = other.coordinates[i];
            }

            this->last = other.last;
        }
        return *this;
    }

    ~Runner()
    {
        delete[] coordinates;
    }

    std::pair<int, int> get(int i)
    {
        return coordinates[i];
    };

    void update(char** maze)
    {

        for (int i = 0; i < size-1; i++)
        {
            coordinates[i] = coordinates[i + 1];
        }

        std::vector<Direction> canMove;
        canMove.reserve(4);

        int x = coordinates[size - 1].first;
        int y = coordinates[size - 1].second;
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

        assert(canMove.size() > 0);

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
                assert(false);
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

        coordinates[size - 1] = std::pair<int, int>(x, y);

        last = getOp(next);
    }

};

class LobbyEffectGenerator
{

public:

    static const char WALL = '0';


    LobbyEffectGenerator();

    char*& operator[](size_t i);

    void update();
    void drawLine(char val, int x, int y, int length);

    std::vector<Runner>& getRunners();

private:

    char** maze;
    std::vector<Runner> runners;

};


#endif //CURSEN_LOBBYEFFECTGENERATOR_H
