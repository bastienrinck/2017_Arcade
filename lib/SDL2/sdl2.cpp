/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by rectoria
*/
#include <stdexcept>
#include "sdl2.hpp"

Arcade::IGraphicLib *lib = nullptr;

__attribute__((constructor)) void init()
{
	lib = new Arcade::Sdl;
}

__attribute__((destructor)) void destruct()
{
	delete lib;
}

extern "C" Arcade::IGraphicLib *entryPoint(void)
{
	return lib;
}

Arcade::Sdl::Sdl()
{
	if (TTF_Init() == -1)
		throw std::runtime_error("SDL TTF initialization failed");
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
		throw std::runtime_error("SDL initialization failed");
}

Arcade::Sdl::~Sdl()
{
	SDL_Quit();
	TTF_Quit();
}

std::string Arcade::Sdl::getName() const
{
	return _name;
}

bool Arcade::Sdl::isOpen() const
{
	return _window != nullptr;
}

void Arcade::Sdl::closeRenderer()
{
	if (_window)
		SDL_DestroyWindow(_window);
	if (_renderer)
		SDL_DestroyRenderer(_renderer);
	if (_texture)
		SDL_DestroyTexture(_texture);
}

void Arcade::Sdl::openRenderer(std::string const &title)
{
	if (_window)
		SDL_DestroyWindow(_window);
	_window = SDL_CreateWindow(title.c_str(), 0,
		0, 1280, 720, SDL_WINDOW_RESIZABLE);
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	_texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA32,
		SDL_TEXTUREACCESS_STREAMING, 1920, 1080);
}

void Arcade::Sdl::clearWindow()
{
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	SDL_RenderClear(_renderer);
}

void Arcade::Sdl::refreshWindow()
{
	SDL_RenderPresent(_renderer);
}

void Arcade::Sdl::drawPixelBox(Arcade::PixelBox const &pB)
{
	SDL_Rect rect{};

	rect.x = static_cast<int>(pB.getX());
	rect.y = static_cast<int>(pB.getY());
	rect.w = static_cast<int>(pB.getWidth());
	rect.h = static_cast<int>(pB.getHeight());
	SDL_UpdateTexture(_texture, &rect, &pB.getPixelArray()[0],
		static_cast<int>(pB.getWidth() * 4));
	SDL_RenderCopy(_renderer, _texture, &rect, &rect);
}

void Arcade::Sdl::drawText(Arcade::TextBox const &tB)
{
	auto raw = (unsigned char *)tB.getColor();

	SDL_Color fgColor = {raw[0], raw[1], raw[2], raw[3]};
	raw = (unsigned char *)tB.getBackgroundColor();
	SDL_Color bgColor = {raw[0], raw[1], raw[2], raw[3]};
	_font = TTF_OpenFont("ressources/fonts/Times New Roman.ttf",
		static_cast<int>(tB.getFontSize()));
	auto surface = TTF_RenderText_Shaded(_font, tB.getValue().c_str(), fgColor,
		bgColor);
	SDL_Rect rect = {static_cast<int>(tB.getX()),
		static_cast<int>(tB.getY()), surface->w, surface->h};
	_text = SDL_CreateTextureFromSurface(_renderer, surface);
	SDL_RenderCopy(_renderer, _text, nullptr, &rect);
	TTF_CloseFont(_font);
}

bool Arcade::Sdl::pollEvents()
{
	SDL_Event event{};
	bool ret = false;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN &&
			_keyMap.count(event.key.keysym.sym)) {
			_events.push_back(_keyMap[event.key.keysym.sym]);
			ret = true;
		}
	}
	return ret;
}

Arcade::Keys Arcade::Sdl::getLastEvent()
{
	Arcade::Keys key = Arcade::Keys::NONE;

	if (!_events.empty()) {
		key = _events.front();
		_events.pop_front();
	}
	return key;
}

void Arcade::Sdl::clearEvents()
{
	_events.clear();
}

Arcade::Vect<size_t> Arcade::Sdl::getScreenSize() const
{
	int x = 0;
	int y = 0;

	SDL_GetWindowSize(_window, &x, &y);
	return {static_cast<size_t>(x), static_cast<size_t>(y)};
}

size_t Arcade::Sdl::getMaxY() const
{
	int y = 0;

	SDL_GetWindowSize(_window, nullptr, &y);
	return static_cast<size_t >(y);
}

size_t Arcade::Sdl::getMaxX() const
{
	int x = 0;

	SDL_GetWindowSize(_window, &x, nullptr);
	return static_cast<size_t >(x);
}
