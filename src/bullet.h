#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Bullet
{
 private:
  float radius;
  float angle;
  sf::VertexArray line;
 public:
  Bullet();
  Bullet(float tx, float ty, sf::Color color);

  void setAngle(float radians);
  void setStart(float tx, float ty);
  void setColor(sf::Color color);
  void setRadius(float size);
  void setEnd(sf::Vector2f point);
  float getRadius();
  float getAngle();
  sf::Vector2f getEnd();
  sf::Vector2f getStart();
  sf::VertexArray getLine();
  
};

#endif
