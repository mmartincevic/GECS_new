#ifndef __FRAMES_PER_SECOND_H__
#define __FRAMES_PER_SECOND_H__

#include <chrono>
#include <vector>

class FPS
{
	using Clock = std::chrono::steady_clock;
	using FrameCount = uint32_t;
	using FrameTime = std::chrono::duration<float>;

	static constexpr FrameTime INTERVAL{ FrameTime(1) };

private:

	Clock::time_point	m_LastUpdate;

	FrameCount			m_FrameCount;
	FrameTime			m_AccFrameTime;

	float				m_CurrentFPS;

public:

	FPS();
	~FPS();
	float Update();
	float GetFPS() const;

};

#endif // __FRAMES_PER_SECOND_H__