#ifndef TIMER_H
#define TIMER_H

#include <chrono>

namespace gecs {
    class Timer {
        public:
            using Duration = std::chrono::duration<float, std::milli>;

            static Timer& Instance() {
                static Timer instance;
                return instance;
            }

            void Start() {
                m_StartTime = std::chrono::steady_clock::now();
                m_Running = true;
            }

            void Stop() {
                m_EndTime = std::chrono::steady_clock::now();
                m_Running = false;
            }

            void Reset() {
                m_StartTime = std::chrono::steady_clock::now();
                m_EndTime = m_StartTime;
                m_Running = true;
            }

            Duration Elapsed() const {
                if (m_Running) {
                    return std::chrono::duration_cast<Duration>(std::chrono::steady_clock::now() - m_StartTime);
                }
                else {
                    return std::chrono::duration_cast<Duration>(m_EndTime - m_StartTime);
                }
            }

        private:
            Timer() : m_StartTime(std::chrono::steady_clock::now()), m_EndTime(m_StartTime), m_Running(false) {}

            std::chrono::time_point<std::chrono::steady_clock> m_StartTime;
            std::chrono::time_point<std::chrono::steady_clock> m_EndTime;
            bool m_Running;
    };
};
#endif // TIMER_H