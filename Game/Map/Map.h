#ifndef GAMEMAP_H
#define GAMEMAP_H

#pragma once

#include <vector>
#include "Layer.h"

class Map
{
	public:

		void Render() {
			for (int i = 0; i < m_MapLayers.size(); ++i)
			{
				m_MapLayers[i]->Render();
			}
		}

		void Update() {
			for (int i = 0; i < m_MapLayers.size(); ++i)
			{
				m_MapLayers[i]->Update();
			}
		}

		inline std::vector<Layer*> Layers() { return m_MapLayers; }

	private:
		friend class MapParser;
		std::vector<Layer*> m_MapLayers;
};
#endif // GAMEMAP_H