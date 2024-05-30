#ifndef __ECS_UNCOPIABLE_H__
#define __ECS_UNCOPIABLE_H__

#pragma once

namespace gecs {
	// The Rule of Zero
	class Uncopiable {
		public:
			Uncopiable() = default;
			Uncopiable(Uncopiable&&) = default;
			Uncopiable(const Uncopiable&) = delete;
			Uncopiable& operator=(const Uncopiable&) = delete;
			Uncopiable& operator=(Uncopiable&&) = default;
	};
};

#endif // __ECS_ICOMPONENT_H__