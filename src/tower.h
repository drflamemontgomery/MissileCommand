#ifndef TOWER_H
#define TOWER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Tower
{
 private:
  int x;
  int y;
  sf::Texture skin;
  sf::Sprite sprite;
  sf::Vector2i target;
  bool hasTarget = false;
 public:
  Tower();
  Tower(int tx, int ty);

  void setPosition(int tx, int ty);
  sf::Vector2i getPosition();
  sf::Texture getTexture();
  sf::Sprite getSprite();

  void setTarget(int tx, int ty);
  void removeTarget();
  sf::Vector2i getTarget();
  bool hastarget();
};

#endif
