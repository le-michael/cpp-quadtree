#ifndef QUADTREE_H
#define QUADTREE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class Quadtree {
public:
  const int maxPoints = 4;

  sf::Rect<float> boundary;

  std::vector<sf::Vector2f> points;

  std::unique_ptr<Quadtree> northWest;
  std::unique_ptr<Quadtree> northEast;
  std::unique_ptr<Quadtree> southWest;
  std::unique_ptr<Quadtree> southEast;

  sf::RectangleShape sprite;

  Quadtree(sf::Rect<float> aabb);
  bool insert(sf::Vector2f point);
  std::vector<sf::Vector2f> query(sf::Rect<float> queryRange);
  void subdivide();
  void draw(sf::RenderTarget &target);
  void reset();
};

#endif /* QUADTREE_H */
