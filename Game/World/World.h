#ifndef GAMEWORLD_H__
#define GAMEWORLD_H__

#pragma once

#include "../Utils/SDL_Wrapper.h"
#include "WorldCamera.h"

class World {
    protected:
        World() {};
        ~World() {};

    public:
        static World& Instance() {
            static World instance;
            return instance;
        }

        World(const World&) = delete;
        void operator=(const World&) = delete;

        WorldCamera* Camera();

    private:
        WorldCamera* m_Camera  = nullptr;
};

#endif // GAMEWORLD_H__