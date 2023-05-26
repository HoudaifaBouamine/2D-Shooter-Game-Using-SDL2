#pragma once
#include <iostream>
#include <iomanip>
#include <chrono>
#ifdef WIN32
#define localtime_r(_Time, _Tm) localtime_s(_Tm, _Time)
#endif

struct Benchmark
{

private:

    time_t _start = 0, _end = 0;

    time_t now,then = 0;

public :


    time_t getFPS() {

        tm localTime;
        std::chrono::system_clock::time_point t = std::chrono::system_clock::now();
        now = std::chrono::system_clock::to_time_t(t);
        localtime_r(&now, &localTime);
        const std::chrono::duration<double> tse = t.time_since_epoch();

        now = std::chrono::duration_cast<std::chrono::microseconds>(tse).count();
        time_t def = (float)1000000 / (now - then);
        then = now;

        return def;
    }

    void putFPS(time_t t) {}


    __declspec(property(put = putFPS, get = getFPS)) time_t FPS;
	

    time_t time = 0;


    void start() {

        tm localTime;
        std::chrono::system_clock::time_point t = std::chrono::system_clock::now();
        _start = std::chrono::system_clock::to_time_t(t);
        localtime_r(&_start, &localTime);
        const std::chrono::duration<double> tse = t.time_since_epoch();

        _start = std::chrono::duration_cast<std::chrono::microseconds>(tse).count();
    }

    void end() {

        tm localTime;
        std::chrono::system_clock::time_point t = std::chrono::system_clock::now();
        _end = std::chrono::system_clock::to_time_t(t);
        localtime_r(&_end, &localTime);
        const std::chrono::duration<double> tse = t.time_since_epoch();

        _end = std::chrono::duration_cast<std::chrono::microseconds>(tse).count();
        time = _end-_start;
    }

};

