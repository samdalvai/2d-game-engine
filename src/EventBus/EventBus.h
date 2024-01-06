#ifndef EVENTBUS_H
#define EVENTBUS_H

#include "../Logger/Logger.h"
#include <map>
#include <typeindex>
#include <list>


class Event{
    public:
        Event() = default;
};

class IEventCallback {
    private:

    public:
        virtual ~IEventCallback() = default;
        void Execute(Event& e);
};

template <typename TEvent>
class EventCallback: public IEventCallback {

};

typedef std::list<IEventCallback> HandlerList;

class EventBus{
    private:
        std::map<std::type_index, std::unique_ptr<HandlerList>> subscribers;

    public:
        EventBus() {
            Logger::Log("EventBus constructor called");
        }
        ~EventBus() {
            Logger::Log("EventBus destructor called");
        }

        template <typename TEvent>
        void SubscribeToEvent() {

        }

        template <typename TEvent>
        void EmitEvent() {

        }

};

#endif