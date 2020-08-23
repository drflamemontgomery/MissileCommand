#include "tower.h"

Tower::Tower() {
  x = 0;
  y = 0;
  if(!skin.loadFromFile("src/assets/tower.png"))
	std::cout << "Tower Image Failed to Load" << std::endl;
  sprite.setTexture(skin);
  sprite.setPosition(x, y);
}

Tower::Tower(int tx, int ty) {
  x = tx;
  y = ty;
  if(!skin.loadFromFile("src/assets/tower.png"))
	std::cout << "Tower Image Failed to Load" << std::endl;
  sprite.setTexture(skin);
  sprite.setPosition(x, y);
}

void Tower::kill() {
  dead = true;
}

void Tower::setPosition(int tx, int ty) {
  x = tx;
  y = ty;

  sprite.setPosition(tx, ty);
}

void Tower::setTarget(int tx, int ty) {
  target.x = tx;
  target.y = ty;
  hasTarget = true;
}

sf::Vector2i Tower::getTarget() {
  return target;
}

sf::Vector2i Tower::getPosition() {
  sf::Vector2i pos(x, y);
  
  return pos;
}

sf::Texture Tower::getTexture() {
  return skin;
}

sf::Sprite Tower::getSprite() {
  return sprite;
}

void Tower::removeTarget() {
  hasTarget = false;
}

bool Tower::hastarget() {
  if(dead) {
	return true;
  }
  return hasTarget;
}

bool Tower::isDead() {
  return dead;
}
