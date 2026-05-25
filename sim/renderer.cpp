#include "renderer.h"
#include <stdexcept>
#include <string_view>

Renderer::Renderer(std::string_view title, int width, int height)
    : width_(width), height_(height) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    throw std::runtime_error(SDL_GetError());
  }

  window_ = SDL_CreateWindow(title.data(), width, height, 0);
  if (!window_) {
    throw std::runtime_error(SDL_GetError());
  }

  renderer_ = SDL_CreateRenderer(window_, nullptr);
  if (!renderer_) {
    throw std::runtime_error(SDL_GetError());
  }
}

Renderer::~Renderer() {
  if (renderer_) SDL_DestroyRenderer(renderer_);
  if (window_)   SDL_DestroyWindow(window_);
  SDL_Quit();
}

bool Renderer::poll_events() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_EVENT_QUIT) return false;
  }
  return true;
}

void Renderer::begin_frame() {
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
  SDL_RenderClear(renderer_);
}

void Renderer::end_frame() {
  SDL_RenderPresent(renderer_);
}

void Renderer::draw_color_bars() {
  // EBUカラーバー風の7色
  const SDL_Color colors[] = {
    {192, 192, 192, 255}, // グレー
    {192, 192,   0, 255}, // イエロー
    {  0, 192, 192, 255}, // シアン
    {  0, 192,   0, 255}, // グリーン
    {192,   0, 192, 255}, // マゼンタ
    {192,   0,   0, 255}, // レッド
    {  0,   0, 192, 255}, // ブルー
  };

  const int num_bars = 7;
  const float bar_width = static_cast<float>(width_) / num_bars;

  for (int i = 0; i < num_bars; i++) {
    const auto& c = colors[i];
    SDL_SetRenderDrawColor(renderer_, c.r, c.g, c.b, c.a);

    SDL_FRect rect = {
      i * bar_width,
      0.0f,
      bar_width,
      static_cast<float>(height_)
    };
    SDL_RenderFillRect(renderer_, &rect);
  }
}