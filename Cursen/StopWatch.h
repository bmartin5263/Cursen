//
// Created by Brandon Martin on 12/26/18.
//

#ifndef CURSEN_STOPWATCH_H
#define CURSEN_STOPWATCH_H

#include <chrono>

using namespace std::chrono;
class StopWatch {

public:

    StopWatch() = default;
    StopWatch(const StopWatch& other) = delete;
    StopWatch& operator = (const StopWatch& other) = delete;
    ~StopWatch() = default;

    void tick();
    void tock();

    long long int getMilliseconds();
    long long int getNanoseconds();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::chrono::time_point<std::chrono::high_resolution_clock> end;

};

#endif //CURSEN_STOPWATCH_H
