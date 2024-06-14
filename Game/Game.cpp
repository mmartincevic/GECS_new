#include "Game.h"
#include "Utils/SDL_Wrapper.h"
#include "World/World.h"
#include "Utils/Timer.h"

#include "Resources/SDLRender.h"
#include "Resources/SDLTexture.h"
#include "Resources/SDLCamera.h"
#include "Resources/SDLImgui.h"

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
};

void Game::Initialize(int width, int height, bool fullscreen)
{
    m_WindowWidth	= width;
    m_WindowHeight	= height;
    m_Fullscreen	= fullscreen;
    m_RUN			= TRUE;
};

double OldTime = 0.0;
double NewTime = 0.0;
double DeltaTime = 0.0;

void Game::Run()
{
    if (!m_RUN) return;
    gecs::ECS_Engine.events().subscribe("GAME_QUIT", this, &Game::Terminate);

    const float TargetFrameTime = 6.67f;
    //const float TargetFrameTime = 1.5f;
    auto lastTime = std::chrono::steady_clock::now();

    // Run application
    //while (SDL_Wrapper::getInstance().getWindow() != nullptr)
    while(gecs::ECS_Engine.IsRunning())
    {
        // TODO: Fix Delta time calcs
        auto currentTime = std::chrono::steady_clock::now();
        float deltaTime = std::chrono::duration<float, std::milli>(currentTime - lastTime).count();
        
        /*if (SDL_Wrapper::getInstance().getWindow() == nullptr)
            return;*/


        float dT = Timer::Instance().DeltaTime();
        gecs::ECS_Engine.Update(dT);
        gecs::ECS_Engine.Draw(dT);

        //	// Update FPS counter
        this->m_DeltaTime = this->m_FPS.Update();

        // Update the Game State
        this->UpdateState();

        //	<Game Name> - <GameState> (<fps>)
        char buffer[256]{ 0 };
        sprintf_s(buffer, "%s - %s (%.2f fps)", this->m_GameTitle, this->GetCurrentState()->GetStateType(), this->m_FPS.GetFPS());
        SDL_SetWindowTitle(SDL_Wrapper::getInstance().getWindow(), buffer);

        if (deltaTime < TargetFrameTime) {
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(TargetFrameTime - deltaTime)));
        }

        lastTime = currentTime;
        Timer::Instance().Tick();
    };
};


void Game::Terminate(const gecs::Event& event)
{
    m_RUN = FALSE; // Set NO RUN FOR GAME

    // Terminate ECS
    gecs::Terminate();
};