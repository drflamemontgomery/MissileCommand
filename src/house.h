#ifndef HOUSE_H
#define HOUSE_H

#include <SFML/Graphics.hpp>
#include <iostream>

class House {
 private:
  float x;
  float y;
  sf::Texture skin;
  sf::Sprite sprite;
  bool dead = false;
 public:
  House();
  House(float tx, float ty);

  void reset();
  void kill();
  void setPosition(float tx, float ty);
  sf::Vector2f getPosition();
  sf::Texture getTexture();
  sf::Sprite getSprite();
  bool isDead();
};

#endif
