#ifndef EVENT_H__
#define EVENT_H__

#pragma once

namespace gecs {

	class IEvent
	{
	public:
		virtual ~IEvent() = default;
	};

	template<typename T>
	class Event : public IEvent
	{};


	class EngineEvent : public Event<EngineEvent>
	{};
	/*struct Event {
		virtual ~Event() = default;
	};*/
};

#endif