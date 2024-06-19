#ifndef GAMEWORLD_H__
#define GAMEWORLD_H__

#pragma once

#include <vector>

#include "../Handlers/ImageLayer.h"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_sdl2.h"
#include "imgui/backends/imgui_impl_sdlrenderer2.h"

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


        inline std::vector<ImageLayer*> BgLayers() { return m_BgLayers; }
        void AddLayer(ImageLayer* layer) { m_BgLayers.push_back(layer); }

        inline void ToggleImGui() { m_ShowImGui = !m_ShowImGui; }
        inline bool ImGuiVisible() const { return m_ShowImGui; }

    private:
        std::vector<ImageLayer*> m_BgLayers;
        bool m_ShowImGui = false;
        
};

#endif // GAMEWORLD_H__