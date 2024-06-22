#ifndef GAMEWORLD_H__
#define GAMEWORLD_H__

#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include <functional>

#include "../Handlers/ImageLayer.h"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_sdl2.h"
#include "imgui/backends/imgui_impl_sdlrenderer2.h"

enum class SceneLayer
{
    BACKGROUND = 0,
    LAYER1,
    LAYER2,
    LAYER3,
    LAYER4,
    LAYER5
};

namespace std {
    template <>
    struct hash<SceneLayer> {
        std::size_t operator()(const SceneLayer& layer) const noexcept {
            return static_cast<std::size_t>(layer);
        }
    };
}

struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

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


        //inline std::vector<ImageLayer*> BgLayers() { return m_BgLayers; }

        //void AddLayer(ImageLayer* layer) { m_BgLayers.push_back(layer); }

        // Adds a layer to a specified scene layer
        // Adds a layer to a specified scene layer
        void AddLayer(SceneLayer layer, std::unique_ptr<ImageLayer> imageLayer)
        {
            m_Layers[layer].push_back(std::move(imageLayer));
        }

        const std::vector<std::unique_ptr<ImageLayer>>& GetLayers(SceneLayer layer) const
        {
            return m_Layers.at(layer);
        }

        inline void ToggleImGui() { m_ShowImGui = !m_ShowImGui; }
        inline bool ImGuiVisible() const { return m_ShowImGui; }

    private:
        std::unordered_map<SceneLayer, std::vector<std::unique_ptr<ImageLayer>>, EnumClassHash> m_Layers;
        bool m_ShowImGui = false;
        
};

#endif // GAMEWORLD_H__