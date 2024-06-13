#include "ImGuiSystem.h"

#include "../Utils/SDL_Wrapper.h"
#include "../World/World.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_sdl2.h"
#include "imgui/backends/imgui_impl_sdlrenderer2.h"


void ImGuiSystem::PreUpdate(float dt) {}
void ImGuiSystem::PostUpdate(float dt) {};

void ImGuiSystem::Update(float dt) 
{
    if (!World::Instance().ImGuiVisible() || SDL_Wrapper::getInstance().getWindow() == nullptr) { return; }

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    //bool show_demo_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Start the Dear ImGui frame
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();



    // Rendering
    ImGui::Render();
    SDL_RenderSetScale(SDL_Wrapper::getInstance().getRenderer(), io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    SDL_SetRenderDrawColor(SDL_Wrapper::getInstance().getRenderer(), (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), SDL_Wrapper::getInstance().getRenderer());
};
