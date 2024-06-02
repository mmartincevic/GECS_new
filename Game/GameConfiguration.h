#ifndef GAME_CONFIG_H__
#define GAME_CONFIG_H__

#pragma once


/// Summary:	The game title.
static constexpr const char*				GAME_TITLE{ "GECS Demo" };


/// Summary:	The default player name.
static constexpr const char*				DEFAULT_PLAYER_NAME{ "GECSY" };


// <<<< GAME WINDOW SETTINGS >>>>

/// Summary:	Width of the game window.
static constexpr unsigned int				GAME_WINDOW_WIDTH{ 1024 };

/// Summary:	Height of the game window.
static constexpr unsigned int				GAME_WINDOW_HEIGHT{ 768 };

/// Summary:	True if game should start in fullscreen mode.
static constexpr bool						GAME_WINDOW_FULLSCREEN{ false };


static constexpr float						DELTA_TIME_STEP{ 1.0f / 60.0f };

static constexpr float						PLAYER_SPEED{ 2.0f };

static constexpr float						PLAYER_JUMPING_SPEED{ 30.0f };


static constexpr float						PLAYER_UPDATE_SPEED{ 0.1f };


class GameConfiguration 
{

};

#endif // GAME_CONFIG_H__