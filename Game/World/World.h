#ifndef GAMEWORLD_H__
#define GAMEWORLD_H__

#pragma once

#include "../Utils/SDL_Wrapper.h"
#include "WorldCamera.h"
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

        WorldCamera* Camera();

        inline std::vector<ImageLayer*> BgLayers() { return m_BgLayers; }
        void AddLayer(ImageLayer* layer) { m_BgLayers.push_back(layer); }

        void ImGui() 
        {
            if (SDL_Wrapper::getInstance().getWindow() == nullptr) {  return; }

            ImGuiIO& io = ImGui::GetIO(); (void)io;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

            //bool show_demo_window = true;
            ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

            // Start the Dear ImGui frame
            ImGui_ImplSDLRenderer2_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();

            //// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
            //if (show_demo_window)
            //    ImGui::ShowDemoWindow(&show_demo_window);

            //// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
            //{
            //    static float f = 0.0f;
            //    static int counter = 0;

            //    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            //    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            //    ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state

            //    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            //    ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            //    if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            //        counter++;
            //    ImGui::SameLine();
            //    ImGui::Text("counter = %d", counter);

            //    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            //    ImGui::End();
            //}

            // Rendering
            ImGui::Render();
            SDL_RenderSetScale(SDL_Wrapper::getInstance().getRenderer(), io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
            SDL_SetRenderDrawColor(SDL_Wrapper::getInstance().getRenderer(), (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
           // SDL_RenderClear(SDL_Wrapper::getInstance().getRenderer());
            ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), SDL_Wrapper::getInstance().getRenderer());
        }

    private:
        WorldCamera* m_Camera  = nullptr;
        std::vector<ImageLayer*> m_BgLayers;
        
};

#endif // GAMEWORLD_H__