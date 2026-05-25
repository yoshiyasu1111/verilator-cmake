#pragma once

#include <SDL3/SDL.h>
#include <string_view>

class Renderer {
public:
    Renderer(std::string_view title, int width, int height);
    ~Renderer();

    bool poll_events();

private:
    SDL_Window*   window_   = nullptr;
    SDL_Renderer* renderer_ = nullptr;
};