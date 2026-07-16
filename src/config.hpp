#pragma once
#include <SFML/Graphics.hpp>
namespace conf
{
	//windows configurations
	sf::Vector2u const window_size = { 2560,1440 };
	sf::Vector2f const window_size_f = static_cast<sf::Vector2f>(window_size);
	uint32_t const max_framerate = 144;
	float const dt = 1.f / static_cast<float>(max_framerate);

	//star configurations
	uint32_t const count = 1000;
	float const radius = 10.f;
	float const near = 0.1f;
	float const far = 10.f;
	float const speed = 1.f;
}