#ifndef EVENTBUS_H
#define EVENTBUS_H

#include "../Logger/Logger.h"

class EventBus{
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