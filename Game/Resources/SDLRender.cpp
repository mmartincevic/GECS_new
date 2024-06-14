#include "SDLRender.h"
#include "SDLCamera.h"
#include "../Utils/Vector2D.h"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_sdl2.h"
#include "imgui/backends/imgui_impl_sdlrenderer2.h"

void SDLRender::Initialize()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");

    //Uint32 window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN;
    m_Window = SDL_CreateWindow(
        m_Params.GameTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        m_Params.ScreenWidth, m_Params.ScreenHeight, SDL_WINDOW_OPENGL | (m_Params.Fullscreen ? SDL_WINDOW_FULLSCREEN : (0)));

    if (m_Window == 0) {
        SDL_Log("Unable to create game application window! %s", SDL_GetError());
        throw std::runtime_error("Error: Unable to create main window!");
        exit(-1);
    }

    m_Render = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (m_Render == NULL) {
        SDL_Log("Unable to create SDL renderer! %s", SDL_GetError());
        throw std::runtime_error("Error: Unable to create rendering!");
        exit(-1);
    }
    SDL_SetRenderDrawColor(m_Render, 0, 0, 0, 255);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    //// Setup Dear ImGui style
    ImGui::StyleColorsDark();
    ////ImGui::StyleColorsLight();

    //// Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(m_Window, m_Render);
    ImGui_ImplSDLRenderer2_Init(m_Render);

    SDL_GetWindowPosition(m_Window, &m_Params.ScreenWidth, &m_Params.ScreenHeight);
    SDL_GetWindowSize(m_Window, &m_Params.ScreenWidth, &m_Params.ScreenHeight);
}

void SDLRender::DrawRect(BoundingBox& bbox, ObjectColor& color)
{
    SDL_SetRenderDrawColor(m_Render, color.r, color.g, color.b, color.a);

    Vector2D cameraPos = gecs::ECS_Engine.resources().Manager<SDLCamera>()->Position();

    SDL_Rect boundingBox;
    boundingBox.x = bbox.x - cameraPos.x;
    boundingBox.y = bbox.y - cameraPos.y;
    boundingBox.w = bbox.width;
    boundingBox.h = bbox.height;
    SDL_RenderDrawRect(m_Render, &boundingBox);
}

SDL_Texture* SDLRender::LoadTexture(std::string textureId, std::string filename)
{
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (surface == nullptr)
    {
        gecs::ECS_Engine.logger().Log(gecs::LogType::GECS_ERROR, "FAILED to load texture : " + filename);
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_Render, surface);
    SDL_FreeSurface(surface);

    if (texture == nullptr)
    {
        gecs::ECS_Engine.logger().Log(gecs::LogType::GECS_ERROR, "FAILED to create texture from surface: " + filename);
        return nullptr;
    }
    return texture;
}

void SDLRender::DrawTexture(SDL_Texture* texture, const SDL_Rect* srcRect, 
    const SDL_Rect* dstRect, double angle, const SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(m_Render, texture, srcRect, dstRect, angle, center, flip);
}

void SDLRender::UpdateCameraPosition()
{
    SDL_Rect camera = gecs::ECS_Engine.resources().Manager<SDLCamera>()->GetViewBox();
    SDL_RenderCopy(m_Render, nullptr, nullptr, &camera);
}

void SDLRender::Cleanup()
{
    SDL_SetRenderDrawColor(m_Render, 0, 0, 0, 255);
    SDL_RenderClear(m_Render);
}

void SDLRender::Render()
{
    SDL_RenderPresent(m_Render);
}

void SDLRender::Clear()
{
    gecs::ECS_Engine.logger().Log(gecs::LogType::GECS_INFO, "GECS : Clearing resource - SDLRender.");
    SDL_RenderClear(m_Render);

    if (m_Window)
    {
        SDL_DestroyWindow(m_Window);
        //delete m_Window;
        //m_Window = nullptr;
    }
    if (m_Render)
    {
        SDL_DestroyRenderer(m_Render);
        //delete m_Render;
        //m_Render = nullptr;
    }

    SDL_Quit();
    IMG_Quit();
}