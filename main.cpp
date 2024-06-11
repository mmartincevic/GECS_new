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
/*if (!parser.loadSettings("config/settings.xml")) {
		std::cout << "CANT LOAD IT" << '\n';
	}*/


int main(int argc, const char* args[])
{
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

	return 0;
};