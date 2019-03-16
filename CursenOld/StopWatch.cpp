//
// Created by Brandon Martin on 12/26/18.
//

#include "StopWatch.h"

void StopWatch::tick() {
    start = std::chrono::high_resolution_clock::now();
}

void StopWatch::tock() {
    end = std::chrono::high_resolution_clock::now();
}

long long int StopWatch::getMilliseconds() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

long long int StopWatch::getNanoseconds(){
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}