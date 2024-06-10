#ifndef TILE_H
#define TILE_H

#pragma once

#include <string>

namespace tiller
{
	enum TileFlip
	{
		HORIZONTAL,
		VERTICAL,
		DIAGONAL,
		HEXAGONAL
	};

	struct Tile
	{
		unsigned	gID;
		unsigned	lID;
		int			tilesetID;
		int			layerID;
		int			groupID;
		float		opacity;
		int			width;
		int			height;
		int			displayRow;
		int			displayCol;
		int			matrixRow;
		int			matrixCol;
		int			rotation;
		std::string imageSrc;
		std::string imageName;
	};
};

#endif // TILE_H