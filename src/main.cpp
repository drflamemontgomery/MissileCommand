#include <SFML/Graphics.hpp>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <math.h>
#include <vector>

#include "tower.h"
#include "cursor.h"
#include "explosion.h"
#include "bullet.h"
#include "house.h"

float distance(sf::Vector2f point1, sf::Vector2f point2) {
  float a = abs(point1.x - point2.x + 16);
  float b = abs(point1.y - point2.y);

  return sqrt(a * a + b * b);
}

float angle(sf::Vector2f point1, sf::Vector2f point2) {
  float adjacent = point1.x - point2.x;
  float opposite = point1.y - point2.y;

    return atan2(opposite, adjacent);// * 180/3.14159265);
}

sf::Vector2f polarToCart(float angle, float radius) {
  float x = cos(angle)*radius;
  float y = sin(angle)*radius;
  
  return sf::Vector2f(x, y);
}

int main(void) {
  srand(time(NULL));
  
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

  House house[14];
  house[0].setPosition(83, 546);
  house[1].setPosition(126, 546);
  house[2].setPosition(169, 546);
  house[3].setPosition(212, 546);
  house[4].setPosition(255, 546);
  house[5].setPosition(298, 546);
  house[6].setPosition(341, 546);
  house[7].setPosition(427, 546);
  house[8].setPosition(470, 546);
  house[9].setPosition(513, 546);
  house[10].setPosition(556, 546);
  house[11].setPosition(599, 546);
  house[12].setPosition(642, 546);
  house[13].setPosition(685, 546);
  
  
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
  bullet[0].setStart(56, 538);
  bullet[1].setStart(400, 538);
  bullet[2].setStart(744, 538);

  std::vector<Explosion> explosions;
  std::vector<Bullet> enemies;

  sf::Clock clock;
  float time = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
  time += 2;
  bool playing = true;
  int score = 0;

  sf::Font gamefont;

  if(!gamefont.loadFromFile("src/assets/yoster.ttf"))
	std::cout << "Font Failed to Load" << std::endl;

  sf::Text displayScore;
  displayScore.setFont(gamefont);
  displayScore.setCharacterSize(30);
  displayScore.setFillColor(sf::Color(255, 255, 255));
  displayScore.setPosition(400, 40);
  displayScore.setString(std::to_string(score));
  
  while(window.isOpen()) {
	sf::Event event;
	
	while(playing) {

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
			dst[0] = distance(bullet[0].getStart(),
							  sf::Vector2f(mouse.getPosition(window).x,
										   mouse.getPosition(window).y));
			dst[1] = distance(bullet[1].getStart(),
							  sf::Vector2f(mouse.getPosition(window).x,
										   mouse.getPosition(window).y));
			dst[2] = distance(bullet[2].getStart(),
							  sf::Vector2f(mouse.getPosition(window).x,
										   mouse.getPosition(window).y));
		  
			if((dst[0] < dst[1] || tower[1].hastarget())
			   && (dst[0] < dst[2] || tower[2].hastarget())
			   && !tower[0].hastarget()) {
			
			  tower[0].setTarget(mouse.getPosition(window).x,
								 mouse.getPosition(window).y);
			  bullet[0].setRadius(0);
			  bullet[0].setAngle(angle(bullet[0].getStart(),
									   sf::Vector2f(tower[0].getTarget())));
		    
			}
			else if((dst[1] < dst[2] || tower[2].hastarget())
					&& !tower[1].hastarget()) {
			
			  tower[1].setTarget(mouse.getPosition(window).x,
								 mouse.getPosition(window).y);
			  bullet[1].setRadius(0);
			  bullet[1].setAngle(angle(bullet[1].getStart(),
									   sf::Vector2f(tower[1].getTarget())));
			}
			else if(!tower[2].hastarget()) {
			
			  tower[2].setTarget(mouse.getPosition(window).x,
								 mouse.getPosition(window).y);
			  bullet[2].setRadius(0);
			  bullet[2].setAngle(angle(bullet[2].getStart(),
									   sf::Vector2f(tower[2].getTarget())));
			}
		  
		  
		  }
		}
	  }

	  if(clock.getElapsedTime().asSeconds() >= time) {
		time = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		time += 2;

		enemies.push_back(Bullet(rand() % 800, 0, sf::Color(255, 0, 0)));
		sf::Vector2f vecTarget(rand() % 800, 540);
		enemies.back().setRadius(0);;
		enemies.back().setAngle(angle(enemies.back().getStart(),
									  vecTarget));
		clock.restart();
	  }
	
	  window.clear();

	  window.draw(ground);

	  for(int i = 0; i < sizeof(tower)/sizeof(tower[0]); i++) {
		if(!tower[i].isDead()) {
		  window.draw(tower[i].getSprite());
		}
	  }

	  for(int i = 0; i < sizeof(house)/sizeof(house[0]); i++) {
		if(!house[i].isDead()) {
		  window.draw(house[i].getSprite());
		}
	  }
	  
	  /*window.draw(cursor[0]);
		window.draw(cursor[1]);*/
	  sf::VertexArray cursorRender1 = cursor.getline1();
	  sf::VertexArray cursorRender2 = cursor.getline2();
	  window.draw(cursorRender1);
	  window.draw(cursorRender2);
	
	  for(int i = 0; i < (sizeof(tower)/sizeof(tower[0])); i++) {
		if(tower[i].hastarget() && !tower[i].isDead()) {
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
			bullet[i].setEnd(polarToCart(bullet[i].getAngle(),
										 bullet[i].getRadius()));
		  
			window.draw(bullet[i].getLine());
		  }
		
		}
	  }

	  for(int i = 0; i < enemies.size(); i++) {
		if(enemies.at(i).getEnd().y >= tower[0].getPosition().y) {
		  for(int j = 0; j < sizeof(tower)/sizeof(tower[0]); j++) {
			if(enemies.at(i).getEnd().y >= 564) {
			  Explosion enemyDied(enemies.at(i).getEnd().x,
								  enemies.at(i).getEnd().y,
								  sf::Color(255, 32, 0));
			  enemyDied.harmful = true;
			  explosions.push_back(enemyDied);
			  enemies.erase(enemies.begin() + i);
			  score += 20;
			  displayScore.setString(std::to_string(score));
			}
			else if(enemies.at(i).getEnd().x >= tower[j].getPosition().x
					&& enemies.at(i).getEnd().x <= tower[j].getPosition().x + 32
					&& !tower[j].isDead()) {
			  explosions.push_back(Explosion(enemies.at(i).getEnd().x,
											 enemies.at(i).getEnd().y,
											 sf::Color(255, 32, 0)));
			  enemies.erase(enemies.begin() + i);
			  score += 20;
			  displayScore.setString(std::to_string(score));
			  tower[j].kill();
			  if(tower[0].isDead() &&
				 tower[1].isDead() &&
				 tower[2].isDead()) {
				for(int otherj = 0; otherj < sizeof(house)/sizeof(house[0]);
					otherj++) {
				  if(!house[otherj].isDead()) {
					break;
				  }
				  else if(otherj == (sizeof(house)/sizeof(house[0])-1)) {
					playing = false;
				  }
				}
			  }
		  
			}
		  }

		  for(int j = 0; j < sizeof(house)/sizeof(house[0]); j++) {
			if(enemies.at(i).getEnd().y >= 564) {
			  Explosion enemyDied(enemies.at(i).getEnd().x,
								  enemies.at(i).getEnd().y,
								  sf::Color(255, 32, 0));
			  enemyDied.harmful = true;
			  explosions.push_back(enemyDied);
			  enemies.erase(enemies.begin() + i);
			  score += 20;
			  displayScore.setString(std::to_string(score));
			}
			else if(enemies.at(i).getEnd().x >= house[j].getPosition().x
					&& enemies.at(i).getEnd().x <= house[j].getPosition().x + 32
					&& !house[j].isDead()) {
			  explosions.push_back(Explosion(enemies.at(i).getEnd().x,
											 enemies.at(i).getEnd().y,
											 sf::Color(255, 32, 0)));
			  enemies.erase(enemies.begin() + i);
			  score += 20;
			  displayScore.setString(std::to_string(score));
			  house[j].kill();
			  if(tower[0].isDead() &&
				 tower[1].isDead() &&
				 tower[2].isDead()) {
				for(int otherj = 0; otherj < sizeof(house)/sizeof(house[0]);
					otherj++) {
				  if(!house[otherj].isDead()) {
					break;
				  }
				  else if(otherj == (sizeof(house)/sizeof(house[0])-1)) {
					playing = false;
				  }
				}
			  }
			  
			}
		  }
		  
		  enemies.at(i).setRadius(enemies.at(i).getRadius()+0.5);
		  enemies.at(i).setEnd(polarToCart(enemies.at(i).getAngle(),
										   enemies.at(i).getRadius()));
		  
		  window.draw(enemies.at(i).getLine());
		  
		}
		else {
		  enemies.at(i).setRadius(enemies.at(i).getRadius()+0.5);
		  enemies.at(i).setEnd(polarToCart(enemies.at(i).getAngle(),
										   enemies.at(i).getRadius()));
		
		  window.draw(enemies.at(i).getLine());
		}
	  
	  }
	
	  for(int i = 0; i < explosions.size(); i++) {
		window.draw(explosions.at(i).getSkin());
		if(explosions.at(i).getSize() < 20) {
		  explosions.at(i).grow(0.15f);
		  for(int j = 0; j < enemies.size(); j++) {
			sf::Vector2f explosionVec = explosions.at(i).getPosition();
			explosionVec.x += explosions.at(i).getSize();
			//explosionVec.y += explosions.at(i).getSize();
			if(distance(enemies.at(j).getEnd(),
						explosionVec) <= (explosions.at(i).getSize() + 0.5f)) {
			  Explosion enemyDies(enemies.at(j).getEnd().x,
								  enemies.at(j).getEnd().y,
								  sf::Color(255, 32, 0));
			  enemyDies.harmful = true;
			  explosions.push_back(enemyDies);
			  enemies.erase(enemies.begin() + j);
			  score += 20;
			  displayScore.setString(std::to_string(score));
			}
			 
		  }
		  for(int j = 0; j < sizeof(house)/sizeof(house[0]); j++) {
			if(explosions.at(i).harmful &&
			   explosions.at(i).getPosition().y >= house[j].getPosition().y - 20
			   && !house[j].isDead()) {
			  float testX = explosions.at(i).getPosition().x;
			  float testY = explosions.at(i).getPosition().y;
			  if(explosions.at(i).getPosition().x <=
				 house[j].getPosition().x)
				testX = house[j].getPosition().x;
			  else if(explosions.at(i).getPosition().x >=
					  house[j].getPosition().x + 32)
				testX = house[j].getPosition().x + 32;
			  if(explosions.at(i).getPosition().y
				 <= house[j].getPosition().y)
				testY = house[j].getPosition().y;

			  float distX = explosions.at(i).getPosition().x - testX;
			  float distY = testY - explosions.at(i).getPosition().y;
			  float dist = sqrt( (distX*distX) + (distY*distY) );

			  if(dist <= explosions.at(i).getSize())
				house[j].kill();
				if(tower[0].isDead() &&
				   tower[1].isDead() &&
				   tower[2].isDead()) {
				  for(int otherj = 0; otherj < sizeof(house)/sizeof(house[0]);
					  otherj++) {
					if(!house[otherj].isDead()) {
					  break;
					}
					else if(otherj == (sizeof(house)/sizeof(house[0])-1)) {
					  playing = false;
					}
				  }
				}

			
			}
			for(int j = 0; j < sizeof(tower)/sizeof(tower[0]); j++) {
			  if(explosions.at(i).harmful &&
				 explosions.at(i).getPosition().y >= tower[j].getPosition().y - 20
				 && !tower[j].isDead()) {
				float testX = explosions.at(i).getPosition().x;
				float testY = explosions.at(i).getPosition().y;
				if(explosions.at(i).getPosition().x <=
				   tower[j].getPosition().x)
				  testX = tower[j].getPosition().x;
				else if(explosions.at(i).getPosition().x >=
						tower[j].getPosition().x + 32)
				  testX = tower[j].getPosition().x + 32;
				if(explosions.at(i).getPosition().y
				   <= tower[j].getPosition().y)
				  testY = tower[j].getPosition().y;

				float distX = explosions.at(i).getPosition().x - testX;
				float distY = testY - explosions.at(i).getPosition().y;
				float dist = sqrt( (distX*distX) + (distY*distY) );

				if(dist <= explosions.at(i).getSize()) {
				  tower[j].kill();
				  if(tower[0].isDead() &&
					 tower[1].isDead() &&
					 tower[2].isDead()) {
					for(int otherj = 0; otherj < sizeof(house)/sizeof(house[0]);
						otherj++) {
					  if(!house[otherj].isDead()) {
						break;
					  }
					  else if(otherj == (sizeof(house)/sizeof(house[0])-1)) {
						playing = false;
					  }
					}
				  }
				}
			  
				
			  }
			}
		  }
		}
		else {
		  explosions.erase(explosions.begin() + i);
		}
	  }

	
	  window.draw(displayScore);
	  window.display();
	}

	while(window.pollEvent(event)) {
	  if(event.type == sf::Event::Closed)
		  window.close();
	}
		  
	
	window.clear();
	window.draw(displayScore);
	window.display();
	
  }
  
  return 0;
  
}
