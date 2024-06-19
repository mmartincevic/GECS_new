/*
    Author : Mladen Martincevic
    Date   : 15th June, 2024
    File   : EventterHandler.h

    EventterHandler class.

    All Rights Reserved. (c) Copyright 2016.
*/

#ifndef EVENTTER_HANDLER_H
#define EVENTTER_HANDLER_H

#include <functional>
#include <map>
#include <unordered_set>
#include <string>
#include <vector>
#include <memory>
#include <iostream>

#include "Event.h"
#include "Uncopiable.h"

namespace gecs
{
    class Receiver
    {
    public:
        virtual ~Receiver() = default;
    };


    class EventDispatcher : public Uncopiable
    {
    public:
        using EventCallback = std::function<void(IEvent&)>;
        using SubscriptionID = size_t;

        // Subscribe with member function pointer
        template<typename EventType, typename T>
        void subscribe(const std::string& eventName, T* receiver, void (T::* memberFunc)(EventType&))
        {
            EventCallback callback = [receiver, memberFunc](IEvent& event)
                {
                    (receiver->*memberFunc)(static_cast<EventType&>(event));
                };
            eventMap[eventName].emplace(receiver, std::move(callback));
        }

        // Subscribe with lambda or function pointer, returning a SubscriptionID
        template<typename EventType>
        SubscriptionID subscribe(const std::string& eventName, std::function<void(EventType&)> callback)
        {
            SubscriptionID id = nextSubscriptionID++;
            EventCallback eventCallback = [callback](IEvent& event)
                {
                    callback(static_cast<EventType&>(event));
                };
            lambdaEventMap[eventName].emplace(id, std::move(eventCallback));
            return id;
        }

        void unsubscribe(const std::string& eventName, Receiver* receiver)
        {
            auto it = eventMap.find(eventName);
            if (it != eventMap.end())
            {
                it->second.erase(receiver);
                if (it->second.empty())
                {
                    eventMap.erase(it);
                }
            }
        }

        void unsubscribe(const std::string& eventName, SubscriptionID id)
        {
            auto it = lambdaEventMap.find(eventName);
            if (it != lambdaEventMap.end())
            {
                it->second.erase(id);
                if (it->second.empty())
                {
                    lambdaEventMap.erase(it);
                }
            }
        }

        void unsubscribeAll(Receiver* receiver) {
            for (auto it = eventMap.begin(); it != eventMap.end();) {
                it->second.erase(receiver);
                if (it->second.empty()) {
                    it = eventMap.erase(it);
                }
                else {
                    ++it;
                }
            }
        }

        void Clear();
        void notify(const std::string& eventName, IEvent& event);

    private:
        std::map<std::string, std::unordered_map<Receiver*, EventCallback>> eventMap;
        std::map<std::string, std::unordered_map<SubscriptionID, EventCallback>> lambdaEventMap;
        SubscriptionID nextSubscriptionID = 0;
    };
};
#endif