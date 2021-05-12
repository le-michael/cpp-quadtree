#include "particle.h"
#include <iostream>
#include <random>

Particle::Particle(float x, float y) : x(x), y(y) {
  const float speed = 50;

  float rx = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
  float ry = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

  dx = rx * (2 * speed) - speed;
  dy = ry * (2 * speed) - speed;

  sprite.setRadius(5);
  sprite.setOrigin(sprite.getRadius(), sprite.getRadius());
  sprite.setFillColor(sf::Color(0x8aa2ffff));
}

void Particle::boundaryCheck(std::unique_ptr<Quadtree> &tree) {
  auto boundary = tree->boundary;
  if (x - sprite.getRadius() <= boundary.left ||
      x + sprite.getRadius() >= boundary.width + boundary.left)
    dx *= -1;

  if (y - sprite.getRadius() <= boundary.top ||
      y + sprite.getRadius() >= boundary.top + boundary.height)
    dy *= -1;
}

void Particle::update(std::unique_ptr<Quadtree> &tree, float dt) {
  boundaryCheck(tree);
  x += dx * dt;
  y += dy * dt;
  sprite.setPosition(x, y);
}

void Particle::collisionCheck(std::unique_ptr<Quadtree> &tree) {
  auto contacts = tree->query(sf::Rect(sprite.getGlobalBounds()));
  float r = sprite.getRadius();
  for (auto &&c : contacts) {
    if (x == c.x && y == c.y)
      continue;
    if (((x - c.x) * (x - c.x) + (y - c.y) * (y - c.y)) < r * r) {
      sprite.setFillColor(sf::Color(0xff4545ff));
      return;
    }
  }
  sprite.setFillColor(sf::Color(0x8aa2ffff));
}

void Particle::draw(std::unique_ptr<Quadtree> &tree, sf::RenderTarget &target) {
  collisionCheck(tree);
  target.draw(sprite);
}
