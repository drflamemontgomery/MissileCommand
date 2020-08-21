#include "bullet.h"

Bullet::Bullet() {
  lines = sf::VertexArray(sf::LineStrip, 2);
  
  setPosition(0, 0);
  setColor(sf::Color(255, 255, 255));
  radius = 0;
}

Bullet::Bullet(float tx, float ty, sf::Color color = sf::Color(255, 255, 255)) {
  lines = sf::VertexArray(sf::LineStrip, 2);
  setPosition(tx, ty);
  setColor(color);
  radius = 0;
}

void Bullet::setAngle(float radians) {
  angle = radians;
}

void Bullet::setPosition(float tx, float ty) {
  lines[0].position = sf::Vector2f(tx, ty);
}

void Bullet::setColor(sf::Color color) {
  lines[0].color = color;
  lines[0].color = color;
}

void Bullet::setRadius(float size) {
  radius = size;
}

void Bullet::setPoint2(sf::Vector2f point) {
  point.x = getPosition().x - point.x;
  point.y = getPosition().y - point.y;
  lines[1].position = point;
}

float Bullet::getRadius() {
  return radius;
}

sf::Vector2f Bullet::getPoint2() {
  return lines[1].position;
}

sf::Vector2f Bullet::getPosition() {
  return lines[0].position;
}

sf::VertexArray Bullet::getSkin() {
  return lines;
}

float Bullet::getAngle() {
  return angle;
}
