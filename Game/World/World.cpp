#include "World.h"


WorldCamera* World::Camera()
{
	if (m_Camera == nullptr)
	{
		m_Camera = new WorldCamera();
	}

	return m_Camera;
}