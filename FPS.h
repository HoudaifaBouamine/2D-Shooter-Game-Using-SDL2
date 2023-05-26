#pragma once
#include <iostream>
#include <iomanip>
#include <chrono>
#ifdef WIN32
#define localtime_r(_Time, _Tm) localtime_s(_Tm, _Time)
#endif

struct FPS
{
    
    time_t now,then = 0;

	void calc() {

        tm localTime;
        std::chrono::system_clock::time_point t = std::chrono::system_clock::now();
         now = std::chrono::system_clock::to_time_t(t);
        localtime_r(&now, &localTime);
        const std::chrono::duration<double> tse = t.time_since_epoch();

        now = std::chrono::duration_cast<std::chrono::milliseconds>(tse).count();

        static int counter = 10;

        counter--;

        if (!counter) {

            printf("\nFPS : %d        \n", 1000 / (now - then));

            counter = 10;
        }
        then = now;


    }


};

