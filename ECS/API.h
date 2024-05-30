#ifndef __ECS_API_H__
#define __ECS_API_H__
#pragma once

#include "definitions.h"
#include "Logger.h"
#include "helpers.h"
#include "Uncopiable.h"
#include "IdFactory.h"

namespace gecs {
	class	Engine;
	extern	Engine ECS_Engine;

	void	Initialize();
	void	Terminate();
};
#endif // __ECS_API_H__