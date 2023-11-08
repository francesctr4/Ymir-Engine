#pragma once

#include <iostream>
#include <functional>
#include <vector>

// Event system classes to manage event subscriptions and notifications (to use if needed)

// Since it's a template class, it's not possible to split the class in header and source file :(

template <typename... Args>
class Event {
public:

    using EventHandler = std::function<void(Args...)>;

    void Subscribe(const EventHandler& handler) {

        handlers.push_back(handler);

    }

    void Notify(Args... args) {

        for (const auto& handler : handlers) {

            handler(args...);

        }

    }

private:

    std::vector<EventHandler> handlers;

};

// Example class that triggers events
class EventTrigger {
public:

    Event<> onTrigger; // Define an event with no arguments

    void PerformAction() {
        
        // Notify subscribers that the action was performed
        onTrigger.Notify();

    }

};