#include "SDLImgui.h"
#include "../World/World.h"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_sdl2.h"
#include "imgui/backends/imgui_impl_sdlrenderer2.h"


void SDLImgui::Initialize()
{
    m_Render = gecs::ECS_Engine.resources().Manager<SDLRender>();
    //gecs::ECS_Engine.events().subscribe("GECS_IMGUI_SET", this, &SDLImgui::AddImguiWindow);
}

void SDLImgui::AddImguiWindow(std::shared_ptr<SDLImguiMenuItem> imguiWindow)
{
    menuItems.push_back(imguiWindow);
}

void SDLImgui::Update() 
{
    if (!World::Instance().ImGuiVisible() || m_Render->Window() == nullptr) { return; }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    //bool show_demo_window = true;
    ImGui::StyleColorsDark();

    // Start the Dear ImGui frame
    


    //DrawImGui();
    /* SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
     SDL_SetRenderDrawColor(renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
     SDL_RenderClear(renderer);
     ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
     SDL_RenderPresent(renderer);*/

     // Rendering
};

void SDLImgui::Render()
{
    if (!World::Instance().ImGuiVisible() || m_Render->Window() == nullptr) { return; }

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    bool show_demo_window = true;
    static int counter = 0;
    static float f = 0.0f;

    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(m_Params.ScreenWidth, 30), ImGuiCond_Always);

    ImGui::Begin("GECS ImGUI Debugger", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);     // Create a window called "Hello, world!" and append into it.
    //ImGui::Text("This is some useful text.");                                   // Display some text (you can use a format strings too)

    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("Menu")) {
            for (auto& item : menuItems) {
                if (ImGui::MenuItem(item->GetName())) {
                    item->isOpen = true;
                }
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }


    //ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state

    //ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    //ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

    //if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
    //    counter++;
    //ImGui::SameLine();
    //ImGui::Text("counter = %d", counter);

    //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
   

    for (auto& item : menuItems) {
        if (item->isOpen) {
            item->RenderWindow();
        }
    }

    ImGui::End();
    ImGui::Render();
    SDL_RenderSetScale(m_Render->Renderer(), io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    SDL_SetRenderDrawColor(m_Render->Renderer(), (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), m_Render->Renderer());
}


void SDLImgui::Cleanup() {};
void SDLImgui::Clear() {};