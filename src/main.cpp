#include "particle.h"
#include "quadtree.h"
#include <SFML/Graphics.hpp>
#include <iostream>

const int screenWidth = 800;
const int screenHeight = 800;

int main() {
  sf::RenderWindow window;
  window.create(sf::VideoMode(screenWidth, screenHeight), "Quadtree Demo",
                sf::Style::Titlebar | sf::Style::Close);

  auto tree = std::make_unique<Quadtree>(
      sf::Rect<float>(10, 10, screenWidth - 20, screenHeight - 20));

  std::vector<Particle> particles;

  sf::Clock clock;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (event.type == sf::Event::MouseButtonPressed) {
        auto pos = sf::Mouse::getPosition(window);
        float x = static_cast<float>(pos.x);
        float y = static_cast<float>(pos.y);
        particles.push_back(Particle(x, y));
      }
    }

    tree->reset();

    float dt = clock.restart().asSeconds();
    for (auto &&p : particles) {
      p.update(tree, dt);
      tree->insert(sf::Vector2f(p.x, p.y));
    }

    window.clear(sf::Color(0x201246ff));
    for (auto &&p : particles) {
      p.draw(tree, window);
    }
    tree->draw(window);
    window.display();
  }

  return 0;
}
