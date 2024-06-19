#include "Game.h"
#include "World/World.h"
#include "Utils/Timer.h"

#include "Resources/SDLRender.h"
#include "Resources/SDLTexture.h"
#include "Resources/SDLCamera.h"
#include "Resources/SDLImgui.h"

#include "Systems/RenderSystem.h"
#include "ImGui/GameImGui.h"

Game::Game(const char* name) :
    m_GameTitle(name),
    m_Fullscreen(false),
    m_WindowPosX(-1), m_WindowPosY(-1),
    m_WindowWidth(-1), m_WindowHeight(-1),
    m_DeltaTime(0.0f)
{};

void Game::InitializeECS()
{
    gecs::Initialize();
    RenderParams param;
    param.GameTitle = m_GameTitle;
    param.ScreenWidth = m_WindowWidth;
    param.ScreenHeight = m_WindowHeight;
    gecs::ECS_Engine.resources().AddManager<SDLRender>(param);

    SDLTextureParams textureParams;
    gecs::ECS_Engine.resources().AddManager<SDLTexture>(textureParams);

    SDLCameraParams cameraParams;
    cameraParams.screenWidth = m_WindowWidth;
    cameraParams.screenHeight = m_WindowHeight;
    gecs::ECS_Engine.resources().AddManager<SDLCamera>(cameraParams);

    SDLImguiParams imguiParams;
    imguiParams.ScreenWidth = m_WindowWidth;
    gecs::ECS_Engine.resources().AddManager<SDLImgui>(imguiParams);


    gecs::ECS_Engine.resources().Initialize();

    SetNextState<StateInitializer>();

    gecs::ECS_Engine.resources().Manager<SDLImgui>()->AddImguiWindow(std::make_shared<GameImGui>(this));

    gecs::ECS_Engine.events().subscribe<GameEvent>("GAME_QUIT", this, &Game::Terminate);
    gecs::ECS_Engine.Start();
};

void Game::Initialize(int width, int height, bool fullscreen)
{
    m_WindowWidth	= width;
    m_WindowHeight	= height;
    m_Fullscreen	= fullscreen;
};

double OldTime = 0.0;
double NewTime = 0.0;
double DeltaTime = 0.0;

void Game::Run()
{
    if (!gecs::ECS_Engine.IsRunning())
    {
        return;
    }
    const float TargetFrameTime = 6.67f;
    //const float TargetFrameTime = 1.5f;
    auto lastTime = std::chrono::steady_clock::now();

    // Run application
    while(gecs::ECS_Engine.IsRunning())
    {
        // TODO: Fix Delta time calcs
        auto currentTime = std::chrono::steady_clock::now();
        float deltaTime = std::chrono::duration<float, std::milli>(currentTime - lastTime).count();
        float dT = Timer::Instance().DeltaTime();

        if (!IsPaused() || IsStepFrame())
        {
            m_FrameCount++;

            gecs::ECS_Engine.Update(dT);
            gecs::ECS_Engine.Draw(dT);

            //	// Update FPS counter
            this->m_DeltaTime = this->m_FPS.Update();

            // Update the Game State
            this->UpdateState();

            //	<Game Name> - <GameState> (<fps>)
            char buffer[256]{ 0 };
            sprintf_s(buffer, "%s - %s (%.2f fps)", this->m_GameTitle, this->GetCurrentState()->GetStateType(), this->m_FPS.GetFPS());
            gecs::ECS_Engine.resources().Manager<SDLRender>()->SetWindowTitle(buffer);

            if (deltaTime < TargetFrameTime) {
                std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(TargetFrameTime - deltaTime)));
            }

            lastTime = currentTime;
            Timer::Instance().Tick();

            m_StepFrame = false;
        }
        else
        {
            // This here is hack to freeze game and run frame by frame
            // For this we need to process SDL_Event for ImGui and rendering system
            SDL_PumpEvents();
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                // Add processing of ImGui keyboard and mouse
                ImGui_ImplSDL2_ProcessEvent(&event);
            }
            gecs::ECS_Engine.systems().getSystem<RenderSystem>()->PreUpdate(dT);
            gecs::ECS_Engine.systems().getSystem<RenderSystem>()->Update(dT);
            gecs::ECS_Engine.systems().getSystem<RenderSystem>()->Draw(dT);
        }
    };
};


void Game::Terminate(GameEvent& event)
{
    // Terminate ECS
    gecs::Terminate();
};