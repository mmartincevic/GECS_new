#ifndef EVENTDISPATCHER_H__
#define EVENTDISPATCHER_H__

#pragma once

#include <iostream>
#include <unordered_map>
#include <functional>

#include "Event.h"

namespace gecs {

    class EventDispatcher {
    private:
        std::unordered_map<std::string, std::vector<std::function<void(const Event&)>>> eventListeners;

        template<typename T>
        bool isSameInstance(const std::function<void(const Event&)>& func, T* obj) const {
            typedef void (T::* MemberFunc)(const Event&);
            if (const MemberFunc* target = func.template target<MemberFunc>()) {
                const void* targetObjPtr = *reinterpret_cast<const void* const*>(func.template target<void*>());
                return targetObjPtr == static_cast<const void*>(obj);
            }
            return false;
        }

    public:
        // Subscribe a member function of a class to a specific event
        template<typename EventType, typename T>
        void subscribe(const std::string& eventName, T* obj, void (T::* memberFunction)(const EventType&)) {
            auto boundFunction = std::bind(memberFunction, obj, std::placeholders::_1);
            eventListeners[eventName].push_back([boundFunction](const Event& e) {
                boundFunction(static_cast<const EventType&>(e));
                });
        }

        // Unsubscribe all member functions of a class instance from a specific event
        template<typename EventType, typename T>
        void unsubscribe(const std::string& eventName, T* obj) {
            auto it = eventListeners.find(eventName);
            if (it != eventListeners.end()) {
                auto& listeners = it->second;
                listeners.erase(
                    std::remove_if(listeners.begin(), listeners.end(),
                        [obj, this](const std::function<void(const Event&)>& listener) {
                            const auto* func = listener.target<std::function<void(const EventType&)>>();
                            return func && isSameInstance(*func, obj);
                        }
                    ),
                    listeners.end()
                );
            }
        }

        // Trigger the event with parameters
        void triggerEvent(const std::string& eventName, const Event& params) {
            auto it = eventListeners.find(eventName);
            if (it != eventListeners.end()) {
                for (const auto& listener : it->second) {
                    listener(params);
                }
            }
        }

        // Clean all subscribers from all events
        void Clear() {
            eventListeners.clear();
        }
    };

    //class EventDispatcher {
    //private:
    //    std::unordered_map<std::string, std::vector<std::function<void(const Event&)>>> eventListeners;

    //    template<typename T>
    //    bool isSameInstance(const std::function<void(const Event&)>& func, T* obj) const {
    //        typedef void (T::* MemberFunc)(const Event&);
    //        if (const MemberFunc* target = func.template target<MemberFunc>()) {
    //            const void* targetObjPtr = *reinterpret_cast<const void* const*>(func.template target<void*>());
    //            return targetObjPtr == static_cast<const void*>(obj);
    //        }
    //        return false;
    //    }

    //public:
    //    // Subscribe a member function of a class to a specific event
    //    template<typename T, typename EventType>
    //    void subscribe(const std::string& eventName, T* obj, void (T::* memberFunction)(const EventType&)) {
    //        auto boundFunction = std::bind(memberFunction, obj, std::placeholders::_1);
    //        eventListeners[eventName].push_back([boundFunction](const Event& e) {
    //            boundFunction(static_cast<const EventType&>(e));
    //            });
    //    }

    //    // Unsubscribe all member functions of a class instance from a specific event
    //    template<typename T>
    //    void unsubscribe(const std::string& eventName, T* obj) {
    //        auto it = eventListeners.find(eventName);
    //        if (it != eventListeners.end()) {
    //            auto& listeners = it->second;
    //            listeners.erase(
    //                std::remove_if(listeners.begin(), listeners.end(),
    //                    [obj, this](const std::function<void(const Event&)>& listener) {
    //                        return isSameInstance(listener, obj);
    //                    }
    //                ),
    //                listeners.end()
    //            );
    //        }
    //    }

    //    // Trigger the event with parameters
    //    void triggerEvent(const std::string& eventName, const Event& params) {
    //        auto it = eventListeners.find(eventName);
    //        if (it != eventListeners.end()) {
    //            for (const auto& listener : it->second) {
    //                listener(params);
    //            }
    //        }
    //    }
    //};



    //class EventDispatcher {
    //    private:
    //        std::unordered_map<std::string, std::vector<std::function<void(const Event&)>>> eventListeners;

    //        template<typename T>
    //        bool compareFunctions(const std::function<void(const Event&)>& lhs, T* obj, void (T::* memberFunction)(const Event&)) {
    //            auto targetFunc = std::bind(memberFunction, obj, std::placeholders::_1);
    //            return lhs.target_type() == targetFunc.target_type() && lhs.target<void(const Event&)>() == targetFunc.target<void(const Event&)>();
    //        }

    //        bool compareFunctions(const std::function<void(const Event&)>& lhs, const std::function<void(const Event&)>& rhs) {
    //            return lhs.target_type() == rhs.target_type() && lhs.target<void(const Event&)>() == rhs.target<void(const Event&)>();
    //        }

    //    public:
    //        // Subscribe a member function of a class to a specific event
    //        template<typename T>
    //        void subscribe(const std::string& eventName, T* obj, void (T::* memberFunction)(const Event&)) {
    //            auto boundFunction = std::bind(memberFunction, obj, std::placeholders::_1);
    //            subscribe(eventName, boundFunction);
    //        }

    //        // Subscribe a lambda function to a specific event
    //        void subscribe(const std::string& eventName, const std::function<void(const Event&)>& listener) {
    //            auto it = eventListeners.find(eventName);
    //            if (it != eventListeners.end()) {
    //                // Check if the listener is already subscribed
    //                for (const auto& existingListener : it->second) {
    //                    if (existingListener.target_type() == listener.target_type()) {
    //                        //throw std::runtime_error("Listener already subscribed to the event.");
    //                        return;
    //                    }
    //                }
    //            }
    //            eventListeners[eventName].push_back(listener);
    //        }

    //        // Subscribe a lambda function from a class method to a specific event
    //        template<typename T>
    //        void subscribe(const std::string& eventName, T* obj, const std::function<void(const Event&)>& memberFunction) {
    //            auto boundFunction = std::bind(memberFunction, obj, std::placeholders::_1);
    //            subscribe(eventName, boundFunction);
    //        }

    //        // Trigger the event with parameters
    //        void triggerEvent(const std::string& eventName, const Event& params) {
    //            auto it = eventListeners.find(eventName);
    //            if (it != eventListeners.end()) {
    //                for (const auto& listener : it->second) {
    //                    listener(params);
    //                }
    //            }
    //        }
    //};

};

#endif