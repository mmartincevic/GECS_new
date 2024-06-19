#include "EventDispatcher.h"

using namespace gecs;

void EventDispatcher::notify(const std::string& eventName, IEvent& event)
{
    auto it = eventMap.find(eventName);
    if (it != eventMap.end()) {
        for (auto& [receiver, callback] : it->second) {
            callback(event);
            if (eventName == "GAME_QUIT") { return; }
        }
    }

    // Notify lambda or function pointer subscribers
    auto lambdaIt = lambdaEventMap.find(eventName);
    if (lambdaIt != lambdaEventMap.end())
    {
        for (auto& [id, callback] : lambdaIt->second)
        {
            callback(event);
        }
    }
}

void EventDispatcher::Clear()
{

    std::vector<std::string> eventsToClear;

    // Add all event names to clear from eventMap
    for (auto& [eventName, receivers] : eventMap) {
        eventsToClear.push_back(eventName);
    }

    // Clear the eventMap entries
    for (const auto& eventName : eventsToClear) {
        eventMap.erase(eventName);
    }

    // Clear lambdaEventMap similarly
    std::vector<std::string> lambdaEventsToClear;

    for (auto& [eventName, subscriptions] : lambdaEventMap) {
        lambdaEventsToClear.push_back(eventName);
    }

    for (const auto& eventName : lambdaEventsToClear) {
        lambdaEventMap.erase(eventName);
    }
}