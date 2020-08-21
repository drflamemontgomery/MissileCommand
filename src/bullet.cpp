#include "bullet.h"

Bullet::Bullet() {
  line = sf::VertexArray(sf::LineStrip, 2);
  
  setStart(0, 0);
  setColor(sf::Color(255, 255, 255));
  radius = 0;
}

Bullet::Bullet(float tx, float ty, sf::Color color = sf::Color(255, 255, 255)) {
  line = sf::VertexArray(sf::LineStrip, 2);
  setStart(tx, ty);
  setColor(color);
  radius = 0;
}

void Bullet::setAngle(float radians) {
  angle = radians;
}

void Bullet::setStart(float tx, float ty) {
  line[0].position = sf::Vector2f(tx, ty);
}

void Bullet::setColor(sf::Color color) {
  line[0].color = color;
  line[0].color = color;
}

void Bullet::setRadius(float size) {
  radius = size;
}

void Bullet::setEnd(sf::Vector2f point) {
  point.x = getStart().x - point.x;
  point.y = getStart().y - point.y;
  line[1].position = point;
}

float Bullet::getRadius() {
  return radius;
}

sf::Vector2f Bullet::getEnd() {
  return line[1].position;
}

sf::Vector2f Bullet::getStart() {
  return line[0].position;
}

sf::VertexArray Bullet::getLine() {
  return line;
}

float Bullet::getAngle() {
  return angle;
}
