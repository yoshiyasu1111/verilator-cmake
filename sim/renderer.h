#pragma once

#include <SDL3/SDL.h>
#include <string_view>

class Renderer {
public:
    Renderer(std::string_view title, int width, int height);
    ~Renderer();

    bool poll_events();
    void begin_frame();
    void end_frame();
    void draw_color_bars(const std::array<uint8_t, 7>& r,
                         const std::array<uint8_t, 7>& g,
                         const std::array<uint8_t, 7>& b);

private:
    SDL_Window*   window_   = nullptr;
    SDL_Renderer* renderer_ = nullptr;
    int width_;
    int height_;
};