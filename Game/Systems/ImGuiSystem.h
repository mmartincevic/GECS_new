#ifndef IMGUI_SYSTEM_H__
#define IMGUI_SYSTEM_H__

#pragma once
#include <SDL.h>

#include "../ECS/API.h"
#include "../ECS/ECS.h"
#include "../ECS/System.h"


class ImGuiSystem : public gecs::System<ImGuiSystem>
{
    public:
        ImGuiSystem() = default;
        ~ImGuiSystem() = default;

        virtual void PreUpdate(float dt) override;
        virtual void Update(float dt) override;
        virtual void PostUpdate(float dt) override;
        virtual void Clear() {};
};
#endif
