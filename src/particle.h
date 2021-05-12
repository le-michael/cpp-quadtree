#ifndef PARTICLE_H
#define PARTICLE_H
#include "quadtree.h"
#include <SFML/Graphics.hpp>

class Particle {
private:
  void boundaryCheck(std::unique_ptr<Quadtree> &tree);
  void collisionCheck(std::unique_ptr<Quadtree> &tree);

public:
  float dx, dy;
  float x, y;

  sf::CircleShape sprite;

  void update(std::unique_ptr<Quadtree> &tree, float dt);
  void draw(std::unique_ptr<Quadtree> &tree, sf::RenderTarget &target);

  Particle(float x, float y);
};

#endif /* PARTICLE_H */
