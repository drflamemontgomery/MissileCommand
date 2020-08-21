#include "explosion.h"

Explosion::Explosion(float tx, float ty) {
  x = tx;
  y = ty;

  radius = 2;

  skin.setPosition(x-radius, y-radius);
  skin.setRadius(radius);
  skin.setFillColor(sf::Color(255, 0, 0));
}

Explosion::Explosion(float tx, float ty, sf::Color color) {
  x = tx;
  y = ty;

  radius = 0.5;

  skin.setPosition(x-radius, y-radius);
  skin.setRadius(radius);
  skin.setFillColor(color);
}

void Explosion::grow(float amount) {
  radius += amount;
  skin.setPosition(x-radius, y-radius);
  skin.setRadius(radius);
}

float Explosion::getSize() {
  return radius;
}

sf::Vector2f Explosion::getPosition() {
  return sf::Vector2f(x, y);
}

sf::CircleShape Explosion::getSkin() {
  return skin;
}
