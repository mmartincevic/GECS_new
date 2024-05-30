///-------------------------------------------------------------------------------------------------
/// File:	main.cpp.
///
/// Summary:	GECS DEMO APP entry point.
///-------------------------------------------------------------------------------------------------

#include <iostream>
#include <numeric>
#include <filesystem>

#include "Game/Game.h"
#include "ECS/XMLSettingsParser.h"

//gecs::XMLSettingsParser& parser = gecs::XMLSettingsParser::getInstance();

int main(int argc, const char* args[])
{
	/*if (!parser.loadSettings("config/settings.xml")) {
		std::cout << "CANT LOAD IT" << '\n';
	}*/

	//std::string gameTitle = parser.getSetting("game.name");
	Game* g_GameInstance = new Game(GAME_TITLE);

	g_GameInstance->Initialize(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT, GAME_WINDOW_FULLSCREEN);
	g_GameInstance->InitializeSDL();
	g_GameInstance->InitializePhysics();
	g_GameInstance->InitializeECS();

	//// enter game main-loop
	g_GameInstance->Run();

	delete g_GameInstance;
	g_GameInstance = nullptr;

	/*ECS_Engine.events().triggerEvent("PLAYER_RUNNING", {});

	ECS_Engine.events().subscribe("PLAYER_RUNNING", [](const Event& params) {
		std::cout << "IDEMO" << std::endl;
	});
	ECS_Engine.events().triggerEvent("PLAYER_RUNNING", {});*/

	return 0;
};