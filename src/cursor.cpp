#include "cursor.h"

Cursor::Cursor() {
  line1 = sf::VertexArray(sf::LineStrip, 2);
  line2 = sf::VertexArray(sf::LineStrip, 2);
  
  setPosition(0, 0);
  setColor(sf::Color(255, 255, 255));

  x = 3;
  y = 3;
}

Cursor::Cursor(float tx, float ty) {
  setPosition(tx, ty);
  setColor(sf::Color(255, 255, 255));
}

Cursor::Cursor(float tx, float ty, sf::Color color) {
  setPosition(tx, ty);

  setColor(color);
}

void Cursor::setPosition(float tx, float ty) {
  x = tx;
  y = ty;

  line1[0].position = sf::Vector2f(x-3, y-3);
  line1[1].position = sf::Vector2f(x+3, y+3);

  line2[0].position = sf::Vector2f(x+3, y-3);
  line2[1].position = sf::Vector2f(x-3, y+3);
}

void Cursor::setColor(sf::Color color) {
  line1[0].color = color;
  line1[1].color = color;
  line2[0].color = color;
  line2[1].color = color;
}

sf::VertexArray Cursor::getline1() {
  return line1;
}

sf::VertexArray Cursor::getline2() {
  return line2;
}

sf::Vector2f Cursor::getPosition() {
  return sf::Vector2f(x, y);
}
