#include "Game.h"
#include "Utils/SDL_Wrapper.h"
#include "TextureManager.h"
#include "World.h"

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
	SetNextState<StateInitializer>();
};

void Game::InitializeSDL()
{
	SDL_Wrapper::getInstance().InitializeSDL(m_GameTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_WindowWidth, m_WindowHeight, false);
};

void Game::InitializePhysics()
{
	World::Get().InitializePhysics();
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

	const float TargetFrameTime = 16.67f;
	auto lastTime = std::chrono::steady_clock::now();

	// Run application
	while (SDL_Wrapper::getInstance().getWindow() != nullptr)
	{
		auto currentTime = std::chrono::steady_clock::now();
		float deltaTime = std::chrono::duration<float, std::milli>(currentTime - lastTime).count();

		if (SDL_Wrapper::getInstance().getWindow() == nullptr)
			return;

		// Update box2d physics world
		//World::Get().GetPhysicsWorld()->Step(DELTA_TIME_STEP, 8, 4);
		//World::Get().GetPhysicsWorld()->Step(DELTA_TIME_STEP, 8, 4);

		// Update Engine
		gecs::ECS_Engine.Update(deltaTime);

		//	// Update FPS counter
		this->m_DeltaTime = this->m_FPS.Update();

		// Update the Game State
		this->UpdateState();

		//	<Game Name> - <GameState> (<fps>)
		char buffer[256]{ 0 };
		//sprintf_s(buffer, "%s - %s (%.2f fps)", this->m_GameTitle, GameState2String[(size_t)this->GetActiveState()], this->m_FPS.GetFPS());
		sprintf_s(buffer, "%s - %s (%.2f fps)", this->m_GameTitle, this->GetCurrentState()->GetStateType(), this->m_FPS.GetFPS());
		SDL_SetWindowTitle(SDL_Wrapper::getInstance().getWindow(), buffer);

		if (deltaTime < TargetFrameTime) {
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(TargetFrameTime - deltaTime)));
		}

		lastTime = currentTime;
	}; // MAIN GAME LOOP!
};


void Game::Terminate(const gecs::Event& event)
{
	m_RUN = FALSE; // Set NO RUN FOR GAME

	//// Terminate ECS
	gecs::Terminate();

	SDL_Wrapper::getInstance().Clear();
	TextureManager::Instance().Clean();

	//// Terminate SDL
	SDL_Quit();
	IMG_Quit();
};