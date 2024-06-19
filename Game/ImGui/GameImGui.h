#ifndef GAMEIMGUI_H
#define GAMEIMGUI_H

#include "../Resources/SDLImgui.h"
#include "imgui/imgui.h"


class GameImGui : public SDLImguiMenuItem
{
public:
    GameImGui(Game* game) : m_Game(game) {}

    const char* GetName() const override {
        return "Game Settings";
    }

    virtual void RenderWindow() override {

        ImGui::SeparatorText("Game settings");
        ImGui::Begin("Game stuff", &isOpen);
        ImGui::Text("Frames passed: %d", m_Game->FrameCounter());

        std::string game_state = (m_Game->IsPaused()) ? "FREEZE" : "RUNNING";
        ImGui::Text("Game state: %s", game_state.c_str());

        ImGui::SeparatorText("Cheats:");
        if (ImGui::Button("Freeze game")) {
            m_Game->TogglePause();
        }

        if (ImGui::Button("Next Frame")) {
            m_Game->NextFrame();
        }

        ImGui::End();
    }

private:
    Game* m_Game;
};

#endif