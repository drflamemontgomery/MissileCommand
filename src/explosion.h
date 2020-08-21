#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Explosion {
 private:
  float x;
  float y;
  float radius;
  sf::CircleShape skin;
 public:
  Explosion(float tx, float ty);
  Explosion(float tx, float ty, sf::Color);

  void grow(float amount);
  float getSize();
  sf::Vector2f getPosition();
  sf::CircleShape getSkin();
};

#endif
