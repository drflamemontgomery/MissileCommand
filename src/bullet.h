#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Bullet
{
 private:
  float radius;
  float angle;
  sf::VertexArray lines;
 public:
  Bullet();
  Bullet(float tx, float ty, sf::Color color);

  void setAngle(float radians);
  void setPosition(float tx, float ty);
  void setColor(sf::Color color);
  void setRadius(float size);
  void setPoint2(sf::Vector2f point);
  float getRadius();
  float getAngle();
  sf::Vector2f getPoint2();
  sf::Vector2f getPosition();
  sf::VertexArray getSkin();
  
};

#endif
