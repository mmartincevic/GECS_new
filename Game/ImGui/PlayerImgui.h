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

        ImGui::SeparatorText("PLAYER General:");

        ImGui::Text("Player entity ID: %d", m_Player->GetID());
        std::string state = m_Player->GetStateTranslate();
        ImGui::Text("Player state: %s", state.c_str());

        ImGui::Text("Player entity position X: %f", playerPosition.x);
        ImGui::Text("Player entity position Y: %f", playerPosition.y);

        ImGui::SeparatorText("PLAYER Position:");

        ImGuiInputTextFlags flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll;
        if (ImGui::InputFloat2("Position", pos,"%.3f", flags)) {
            m_Player->PlayerTransform()->SetPositionX(pos[0]);
            m_Player->PlayerTransform()->SetPositionY(pos[1]);
        }

        // Add your settings and content for the Camera Settings window here
        //ImGui::Text("This is the Camera Settings window.");
        
        //ImGui::SeparatorText("ABOUT THIS DEMO:");
        //ImGui::BulletText("See the ShowDemoWindow() code in imgui_demo.cpp. <- you are here!");
        static int playerx = m_Player->PlayerTransform()->Position().x;
        if (ImGui::InputInt("PlayerPosition X", &playerx))
        {
            m_Player->PlayerTransform()->SetPositionX(playerx);
        }

        static int playery = m_Player->PlayerTransform()->Position().y;
        if (ImGui::InputInt("PlayerPosition Y", &playery))
        {
            m_Player->PlayerTransform()->SetPositionY(playery);
        }

        /*static int always_on = 0;
        ImGui::RadioButton("Off", &always_on, 0);
        ImGui::SameLine();
        ImGui::RadioButton("Always On (Simple)", &always_on, 1);
        ImGui::SameLine();
        ImGui::RadioButton("Always On (Advanced)", &always_on, 2);*/

        ImGui::SeparatorText("Cheats:");

        if (ImGui::Button("Reset Player Position")) {
            m_Player->PlayerTransform()->SetPositionX(100);
            m_Player->PlayerTransform()->SetPositionY(100);
        }

        ImGui::End();
    }

private:
    Player* m_Player;
};

#endif