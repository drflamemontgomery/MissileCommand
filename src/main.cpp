#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <math.h>
#include "tower.h"
#include "cursor.h"


void explode(sf::RenderWindow* window) {
  
}

float distance(sf::Vector2f point1, sf::Vector2f point2) {
  float a = abs(point1.x - point2.x);
  float b = abs(point1.y - point2.y);

  return sqrt(a * a + b * b);
}

float angle(sf::Vector2f point1, sf::Vector2f point2) {
  float adjacent = point1.x - point2.x;
  float opposite = point1.y - point2.y;

  std::cout << "point1 (" << point1.x << ", " << point1.y << ")" << std::endl;
  std::cout << "point2 (" << point2.x << ", " << point2.y << ")" << std::endl;
  std::cout << "o " << opposite << std::endl;
  std::cout << "a " << adjacent << std::endl;
  std::cout << "atan " << atan(opposite/adjacent) << std::endl;
  
  return (atan2(opposite, adjacent) * 180/3.14159265);
}

int main(void) {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Missile Command");
  window.setMouseCursorVisible(false);

  sf::Mouse mouse;
  
  /*sf::Texture cursorSkin;
  if(!cursorSkin.loadFromFile("src/assets/cursor.png"))
	return 2;
  
  sf::Sprite cursor;
  cursor.setTexture(cursorSkin);
  cursor.setPosition(10, 10);*/


  //cursor original
  
  /*sf::RectangleShape cursor[2];
  cursor[0].setSize(sf::Vector2f(11, 1));
  cursor[0].setOrigin(6,0);
  cursor[0].rotate(45);
  
  cursor[1].setSize(sf::Vector2f(11, 1));
  cursor[1].rotate(135);
  cursor[1].setOrigin(5, 0);*/

  Cursor cursor;

  Cursor target;
  target.setColor(sf::Color(255, 0, 0));
  
  Tower tower[3];

  tower[0].setPosition(40, 540);
  tower[1].setPosition(384, 540);
  tower[2].setPosition(728, 540);
  
  /*sf::Vertex ground[2];
  ground[0].position = sf::Vector2f(0, 541);
  ground[0].color = sf::Color(255, 255, 255);
  ground[0].position = sf::Vector2f(800, 541);
  ground[0].color = sf::Color(255, 255, 255);*/

  sf::VertexArray ground(sf::LineStrip, 2);
  ground[0].position = sf::Vector2f(0, 564);
  ground[0].color = sf::Color(255, 255, 255);
  ground[1].position = sf::Vector2f(800, 564);
  ground[1].color = sf::Color(255, 255, 255);

  sf::RectangleShape bullet[3];
  bullet[0].setPosition(56.5, 538);
  bullet[1].setPosition(400.5, 538);
  bullet[2].setPosition(744.5, 538);
  for(int i = 0; i < 3; i++) {
	bullet[i].setOutlineColor(sf::Color(255, 255, 255));
  }
  
  while(window.isOpen()) {
	sf::Event event;

	int mouseX = mouse.getPosition(window).x;
	int mouseY = mouse.getPosition(window).y;


	// cursor original
	
	/*cursor[0].setPosition(mouseX, mouseY);
	  cursor[1].setPosition(mouseX, mouseY);*/
	cursor.setPosition(mouseX, mouseY);

	if(window.getSize() != sf::Vector2u(800, 600)) {
	  window.setSize(sf::Vector2u(800, 600));
	}
	
	while(window.pollEvent(event)) {
	  if(event.type == sf::Event::Closed) {
		window.close();
	  }
	  
	  if(event.type == sf::Event::MouseButtonReleased) {
		if(event.mouseButton.button == sf::Mouse::Left) {
		  float dst[3];
		  dst[0] = distance(sf::Vector2f(bullet[0].getPosition()),
							sf::Vector2f(mouse.getPosition(window).x,
										 mouse.getPosition(window).y));
		  dst[1] = distance(sf::Vector2f(bullet[1].getPosition()),
							sf::Vector2f(mouse.getPosition(window).x,
										 mouse.getPosition(window).y));
		  dst[2] = distance(sf::Vector2f(bullet[2].getPosition()),
							sf::Vector2f(mouse.getPosition(window).x,
										 mouse.getPosition(window).y));
		  
		  if((dst[0] < dst[1] || tower[1].hastarget())
			 && (dst[0] < dst[2] || tower[2].hastarget())
			 && !tower[0].hastarget()) {
			
			tower[0].setTarget(mouse.getPosition(window).x,
							   mouse.getPosition(window).y);
			bullet[0].setSize(sf::Vector2f(1, 1));
			bullet[0].setOrigin(1, 0);
			bullet[0].setRotation(0);
			bullet[0].rotate(angle(sf::Vector2f(bullet[0].getPosition()),
								   sf::Vector2f(mouse.getPosition(window).x,
												mouse.getPosition(window).y)));
			
		  }
		  else if((dst[1] < dst[2] || tower[2].hastarget())
				  && !tower[1].hastarget()) {
			
			tower[1].setTarget(mouse.getPosition(window).x,
							   mouse.getPosition(window).y);
			bullet[1].setSize(sf::Vector2f(1, 1));
			bullet[1].setOrigin(1, 0);
			bullet[1].setRotation(0);
			bullet[1].rotate(angle(sf::Vector2f(bullet[1].getPosition()),
								   sf::Vector2f(mouse.getPosition(window).x,
												mouse.getPosition(window).y)));
			
		  }
		  else if(!tower[2].hastarget()) {
			
			tower[2].setTarget(mouse.getPosition(window).x,
							   mouse.getPosition(window).y);
			bullet[2].setSize(sf::Vector2f(1, 1));
			bullet[2].setOrigin(1, 0);
			bullet[2].setRotation(0);
			bullet[2].rotate(angle(sf::Vector2f(bullet[2].getPosition()),
										sf::Vector2f(mouse.getPosition(window).x,
													 mouse.getPosition(window).y)));
		  }
		  
		  
		}
	  }
	}

	
	
	window.clear();

	window.draw(ground);
	
	window.draw(tower[0].getSprite());
	window.draw(tower[1].getSprite());
	window.draw(tower[2].getSprite());

	/*window.draw(cursor[0]);
	  window.draw(cursor[1]);*/
	sf::VertexArray cursorRender1 = cursor.getline1();
	sf::VertexArray cursorRender2 = cursor.getline2();
	window.draw(cursorRender1);
	window.draw(cursorRender2);
	
	for(int i = 0; i < (sizeof(tower)/sizeof(tower[0])); i++) {
	  if(tower[i].hastarget()) {
		target.setPosition(tower[i].getTarget().x,
						   tower[i].getTarget().y);
		window.draw(target.getline1());
		window.draw(target.getline2());

		if(bullet[i].getSize().x >= distance(sf::Vector2f(tower[i].getPosition()),
											 sf::Vector2f(tower[i].getTarget()))) {
		  //explosion
		  tower[i].removeTarget();
		}
		
		bullet[i].setSize(sf::Vector2f(bullet[i].getSize().x+1.5, 1));
		bullet[i].setOrigin(bullet[i].getSize().x, 0);

		window.draw(bullet[i]);
		
	  }
	}
	window.display();
  }
  
  return 0;
  
}
