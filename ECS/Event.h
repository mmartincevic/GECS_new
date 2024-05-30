#ifndef EVENT_H__
#define EVENT_H__

#pragma once

namespace gecs {
	
	struct Event {
		virtual ~Event() = default;
	};
};

#endif