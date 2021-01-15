#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tilemap.h"

class Map{
public:
	Map(int width, int height);
	void addTile(unsigned int id, int x, int y);
	void drawMap(sf::RenderWindow& window, Tilemap tilemap);
private:
	int width, height;
	std::vector< std::vector<unsigned int> > map;
	sf::Sprite spr;
	sf::Texture txt;

};

