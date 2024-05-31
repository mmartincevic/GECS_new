#ifndef TIMER_H__
#define TIMER_H__

#pragma once

#include <iostream>

const int   TARGET_FPS = 150;
const float TARGET_DELTATIME = 1.5f;

class Timer {
    private:
        Timer() {};

    public:
        static Timer& Instance() {
            static Timer instance;
            return instance;
        }
        void Tick();
        inline float DeltaTime() { return m_DeltaTime; }

    private:
        float m_DeltaTime;
        float m_LastTime;
};

#endif