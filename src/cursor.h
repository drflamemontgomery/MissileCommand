#ifndef CURSOR_H
#define CURSOR_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Cursor {
 private:
  sf::VertexArray line1;
  sf::VertexArray line2;
  float x;
  float y;
 public:
  Cursor();
  Cursor(float tx, float ty);
  Cursor(float tx, float ty, sf::Color color);

  void setPosition(float tx, float ty);
  void setColor(sf::Color color);
  sf::VertexArray getline1();
  sf::VertexArray getline2();
};

#endif
