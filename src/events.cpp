#include "events.hpp"

void processEvents(sf::Window& window)
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) 
        {
            if (keyPressed->code == sf::Keyboard::Key::Escape) 
                window.close();
            
        }
    }
}
