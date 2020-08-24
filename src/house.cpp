#include "house.h"

House::House() {
  x = 0;
  y = 0;
  if(!skin.loadFromFile("src/assets/house.png"))
	std::cout << "House Image Failed to Load" << std::endl;
  sprite.setTexture(skin);
  sprite.setPosition(x, y);
}

House::House(float tx, float ty) {
  x = tx;
  y = ty;
  if(!skin.loadFromFile("src/assets/house.png"))
	std::cout << "House Image Failed to Load" << std::endl;
  sprite.setTexture(skin);
  sprite.setPosition(x, y);  
}

void House::reset() {
  dead = false;
}

void House::kill() {
  dead = true;
}

void House::setPosition(float tx, float ty) {
  x = tx;
  y = ty;
  sprite.setPosition(x, y);
}

sf::Vector2f House::getPosition() {
  return sf::Vector2f(x, y);
}

sf::Texture House::getTexture() {
  return skin;
}

sf::Sprite House::getSprite() {
  return sprite;
}

bool House::isDead() {
  return dead;
}
