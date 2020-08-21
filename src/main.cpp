#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include "tower.h"
#include "cursor.h"
#include "explosion.h"
#include "bullet.h"

void explode(sf::RenderWindow* window) {
  
}

float distance(sf::Vector2f point1, sf::Vector2f point2) {
  float a = abs(point1.x - point2.x + 16);
  float b = abs(point1.y - point2.y);

  return sqrt(a * a + b * b);
}

float angle(sf::Vector2f point1, sf::Vector2f point2) {
  float adjacent = point1.x - point2.x;
  float opposite = point1.y - point2.y;

  std::cout << "angle: "<< atan2(opposite, adjacent) << std::endl;
  return atan2(opposite, adjacent);// * 180/3.14159265);
}

sf::Vector2f polarToCart(float angle, float radius) {
  float x = cos(angle)*radius;
  float y = sin(angle)*radius;
  
  return sf::Vector2f(x, y);
}

int main(void) {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Missile Command");
  window.setMouseCursorVisible(false);

  sf::Mouse mouse;

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

  Bullet bullet[3];
  bullet[0].setPosition(56, 538);
  bullet[1].setPosition(400, 538);
  bullet[2].setPosition(744, 538);

  std::vector<Explosion> explosions;
  
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
		  dst[0] = distance(bullet[0].getPosition(),
							sf::Vector2f(mouse.getPosition(window).x,
										 mouse.getPosition(window).y));
		  dst[1] = distance(bullet[1].getPosition(),
							sf::Vector2f(mouse.getPosition(window).x,
										 mouse.getPosition(window).y));
		  dst[2] = distance(bullet[2].getPosition(),
							sf::Vector2f(mouse.getPosition(window).x,
										 mouse.getPosition(window).y));
		  
		  if((dst[0] < dst[1] || tower[1].hastarget())
			 && (dst[0] < dst[2] || tower[2].hastarget())
			 && !tower[0].hastarget()) {
			
			tower[0].setTarget(mouse.getPosition(window).x,
							   mouse.getPosition(window).y);
			bullet[0].setRadius(0);
			bullet[0].setAngle(angle(bullet[0].getPosition(),
									 sf::Vector2f(tower[0].getTarget())));
		    
		  }
		  else if((dst[1] < dst[2] || tower[2].hastarget())
				  && !tower[1].hastarget()) {
			
			tower[1].setTarget(mouse.getPosition(window).x,
							   mouse.getPosition(window).y);
			bullet[1].setRadius(0);
			bullet[1].setAngle(angle(bullet[1].getPosition(),
									 sf::Vector2f(tower[1].getTarget())));
		  }
		  else if(!tower[2].hastarget()) {
			
			tower[2].setTarget(mouse.getPosition(window).x,
							   mouse.getPosition(window).y);
			bullet[2].setRadius(0);
			bullet[2].setAngle(angle(bullet[2].getPosition(),
									 sf::Vector2f(tower[2].getTarget())));
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

		if(bullet[i].getRadius() >= distance(sf::Vector2f(tower[i].getPosition()),
											 sf::Vector2f(tower[i].getTarget()))) {
		  explosions.push_back(Explosion(target.getPosition().x,
										 target.getPosition().y));
		  tower[i].removeTarget();
		}
		else {
		  
		  bullet[i].setRadius(bullet[i].getRadius()+1.5);
		  bullet[i].setPoint2(polarToCart(bullet[i].getAngle(),
										  bullet[i].getRadius()));
		  
		  window.draw(bullet[i].getSkin());
		}
		
	  }
	}

	for(int i = 0; i < explosions.size(); i++) {
	  window.draw(explosions.at(i).getSkin());
	  if(explosions.at(i).getSize() < 20) {
		explosions.at(i).grow(0.1f);
	  }
	  else {
		explosions.erase(explosions.begin() + i);
	  }
	}
	
	window.display();
  }
  
  return 0;
  
}
