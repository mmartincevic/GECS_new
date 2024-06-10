#ifndef TILEERRORSTATUS_H
#define TILEERRORSTATUS_H

#pragma once

#include <string>

namespace tiller {

	enum TileResult
	{
		TOK,
		TERROR
	};
	struct TileError
	{
		TileResult result = TileResult::TOK;
	};
};

#endif // TILEERRORSTATUS_H