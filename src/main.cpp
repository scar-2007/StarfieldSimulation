#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>
#include "events.hpp"
#include "config.hpp"
#include "star.hpp"


std::vector<Star> createStar(uint32_t count , float scale)
{
    std::vector<Star> stars;
    stars.reserve(count);

    //ramdom no. generator
    std::mt19937 generator;
    std::uniform_real_distribution<float>dis(0.0f, 1.0f);

    //star free zone(SFZ)
    sf::Vector2f const window_world_size = conf::window_size_f * conf::near;
    sf::FloatRect const star_free_zone = {-window_world_size*0.5f, window_world_size};

    //create random stars on screen
    for (uint32_t i{ count };i--;)
    {
        float const x = (dis(generator)-0.5f) * conf::window_size_f.x * scale; //-0.5f to set it around origin 
        float const y = (dis(generator)-0.5f) * conf::window_size_f.y * scale; //-0.5f to set it around origin 
        float const z = dis(generator) * (conf::far - conf::near) + conf::near;

        //discard stars in SFZ;
        sf::Vector2f star_free_zone_points = { x,y };
        if (star_free_zone.contains(star_free_zone_points))
        {
            ++i;
            continue;
        }
        //else add it to vector
        stars.push_back({ { x,y },z });

    }

    //ordering depth
    std::sort(stars.begin(), stars.end(), [](Star const& s_1, Star const& s_2) {
        return s_1.z > s_2.z;
        });
    return stars;
}


int main()
{
    sf::RenderWindow window(sf::VideoMode({ conf::window_size.x , conf::window_size.y}), "starField");
    window.setFramerateLimit(conf::max_framerate);

    std::vector<Star> stars = createStar(conf::count , conf::far);

    uint32_t first = 0;
    while (window.isOpen())
    {
        processEvents(window);

        //travel towards z axis
        for (uint32_t i{ conf::count };i--;)
        {
            Star& s = stars[i];
            s.z -= conf::speed * conf::dt;
            if (s.z < conf::near)
            {
                //offset of star
                s.z = conf::far - (conf::near - s.z);

                first = i;
            }
        }

        window.clear();

        sf::CircleShape shape{ conf::radius };
        shape.setOrigin({conf::radius, conf::radius});

        
        for (uint32_t i = 0;i<conf::count;++i)
        {
            uint32_t const idx = (i + first) % conf::count;
            Star const& s = stars[idx];
            float scale = 1.f / s.z; //scaling coeff. which is inverse of the depth
            shape.setPosition(s.position * scale + conf::window_size_f * 0.5f);
            shape.setScale({scale, scale});

            float const depth_ratio = (s.z - conf::near) / (conf::far - conf::near);
            float brightness = 1.0f - depth_ratio;
            auto const b = static_cast<uint8_t>(brightness * 255.f);
            shape.setFillColor({ b,b,b });
            window.draw(shape);
                        
        }


        window.display();
    }
}