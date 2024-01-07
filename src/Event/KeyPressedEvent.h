#ifndef KEYPRESSEDEVENT_H
#define KEYPRESSEDEVENT_H

#include "../EventBus/Event.h"
#include "../ECS/ECS.h"

#include <SDL2/SDL.h>

class KeyPressedEvent: public Event{
    public:
        SDL_Keycode keyCode;
        KeyPressedEvent(SDL_Keycode keyCode): keyCode(keyCode) {}

};

#endif
