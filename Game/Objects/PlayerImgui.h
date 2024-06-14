#ifndef PLAYERIMGUI_H
#define PLAYERIMGUI_H

#pragma once

#include "../Resources/SDLImgui.h"
#include "imgui/imgui.h"


class PlayerImgui : public SDLImguiMenuItem 
{
public:
    PlayerImgui(Player* player) : m_Player(player) {}

    const char* GetName() const override {
        return "Player Settings";
    }

    virtual void RenderWindow() override {

        ImGui::SeparatorText("General player settings");
        ImGui::Begin("Player settings", &isOpen);

        Vector2D playerPosition = m_Player->PlayerTransform()->Origin();
        float pos[2] = { playerPosition.x, playerPosition.y };

        ImGui::Text("Player entity ID: %d", m_Player->GetID());
        ImGui::Text("Player entity position X: %f", playerPosition.x);
        ImGui::Text("Player entity position Y: %f", playerPosition.y);

        ImGuiInputTextFlags flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll;
        if (ImGui::InputFloat2("Position", pos,"%.3f", flags)) {
            m_Player->PlayerTransform()->SetPositionX(pos[0]);
            m_Player->PlayerTransform()->SetPositionY(pos[1]);
        }


        // Add your settings and content for the Camera Settings window here
        ImGui::Text("This is the Camera Settings window.");
        
        ImGui::SeparatorText("ABOUT THIS DEMO:");
        ImGui::BulletText("See the ShowDemoWindow() code in imgui_demo.cpp. <- you are here!");
        static int i0 = 123;
        ImGui::InputInt("input int", &i0);

        static int always_on = 0;
        ImGui::RadioButton("Off", &always_on, 0);
        ImGui::SameLine();
        ImGui::RadioButton("Always On (Simple)", &always_on, 1);
        ImGui::SameLine();
        ImGui::RadioButton("Always On (Advanced)", &always_on, 2);

       

        ImGui::End();
    }

private:
    Player* m_Player;
};

#endif