#ifndef GAMEWORLD_H__
#define GAMEWORLD_H__

#pragma once

#include "../Utils/SDL_Wrapper.h"
#include "WorldCamera.h"
#include <vector>

#include "../Handlers/ImageLayer.h"

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

        inline std::vector<ImageLayer*> BgLayers() { return m_BgLayers; }
        void AddLayer(ImageLayer* layer) { m_BgLayers.push_back(layer); }

    private:
        WorldCamera* m_Camera  = nullptr;
        std::vector<ImageLayer*> m_BgLayers;
        
};

#endif // GAMEWORLD_H__