#pragma once
#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

struct Tile{
	Tile(unsigned int id, sf::IntRect rect)
		:id(id), rect(rect)
	{
	}
	unsigned int id;
	sf::IntRect rect;
};

class Tilemap{
public:
	Tilemap(std::string fileName, int gridWidth=64, int gridHeight=64);
	void drawTiles(sf::RenderWindow* window);
	void initTiles();

	// GETTERS
	sf::Vector2u getTilemapSize();
	sf::IntRect getRectById(unsigned int id);
private:
	sf::Texture texture;
	sf::Sprite sprite;
	std::vector< std::vector<Tile*> > tiles;

	int gridWidth;
	int gridHeight;

	friend class Map;
};

