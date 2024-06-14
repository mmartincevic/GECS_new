#include "TillerImgui.h"

#include "Tiller.h"
#include "Tile.h"
#include "../Resources/SDLCamera.h"

void TillerImgui::RenderWindow() {

    ImGui::SeparatorText("Tiles display & settings");
    ImGui::Begin("Tile display & settings", &isOpen);
    auto m_Camera = gecs::ECS_Engine.resources().Manager<SDLCamera>();
    Vector2D cameraPos = m_Camera->Position();

    for (auto group : tiller::Tiller::Instance().ParsedData())
    {
        int groupId = group.first;

        for (auto layer : group.second)
        {
            int layerId = layer.first;

            for (tiller::Tile tile : layer.second)
            {
                if (ImGui::TreeNode((void*)(intptr_t)tile.gID, "Tile  global id %d, local id %d", tile.gID, tile.lID)) {
                    // Display object details
                    ImGui::Text("ID: %d", tile.lID);
                    ImGui::Text("Position X: %d", (tile.displayCol * tile.width));
                    ImGui::Text("Position Y: %d", tile.displayRow * tile.width);
                    ImGui::TreePop();
                }
            }
        }
    }

    ImGui::End();
}