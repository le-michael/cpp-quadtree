#include "quadtree.h"
#include <iostream>

Quadtree::Quadtree(sf::Rect<float> aabb) : boundary(aabb) {

  sprite.setPosition({aabb.left, aabb.top});
  sprite.setSize({aabb.width, aabb.height});

  sprite.setFillColor({0, 0, 0, 0});
  sprite.setOutlineColor(sf::Color(0xfff6eeff));
  sprite.setOutlineThickness(1);
}

bool Quadtree::insert(sf::Vector2f point) {
  if (!boundary.contains(point)) {
    return false;
  }

  if (points.size() < maxPoints && northWest == nullptr) {
    points.push_back(point);
    return true;
  }

  if (!northWest)
    subdivide();

  if (northWest->insert(point))
    return true;
  if (northEast->insert(point))
    return true;
  if (southWest->insert(point))
    return true;
  if (southEast->insert(point))
    return true;

  return false;
}

std::vector<sf::Vector2f> Quadtree::query(sf::Rect<float> queryRange) {
  std::vector<sf::Vector2f> result;

  if (!boundary.intersects(queryRange)) {
    return result;
  }

  for (auto &&p : points) {
    result.push_back(p);
  }

  if (!northWest) {
    return result;
  }

  auto nw = northWest->query(queryRange);
  result.insert(result.end(), nw.begin(), nw.end());
  auto ne = northEast->query(queryRange);
  result.insert(result.end(), ne.begin(), ne.end());
  auto sw = southWest->query(queryRange);
  result.insert(result.end(), sw.begin(), sw.end());
  auto se = southEast->query(queryRange);
  result.insert(result.end(), se.begin(), se.end());

  return result;
}

void Quadtree::subdivide() {
  const float hWidth = boundary.width / 2;
  const float hHeight = boundary.height / 2;

  northWest = std::make_unique<Quadtree>(
      sf::Rect<float>(boundary.left, boundary.top, hWidth, hHeight));
  northEast = std::make_unique<Quadtree>(
      sf::Rect<float>(boundary.left + hWidth, boundary.top, hWidth, hHeight));
  southWest = std::make_unique<Quadtree>(
      sf::Rect<float>(boundary.left, boundary.top + hHeight, hWidth, hHeight));
  southEast = std::make_unique<Quadtree>(sf::Rect<float>(
      boundary.left + hWidth, boundary.top + hHeight, hWidth, hHeight));
}

void Quadtree::draw(sf::RenderTarget &target) {
  if (!northWest) {
    target.draw(sprite);
    return;
  }
  northWest->draw(target);
  northEast->draw(target);
  southWest->draw(target);
  southEast->draw(target);
}

void Quadtree::reset() {
  points.clear();
  northWest.reset(nullptr);
  northEast.reset(nullptr);
  southWest.reset(nullptr);
  southEast.reset(nullptr);
}
