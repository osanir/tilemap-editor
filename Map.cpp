#include "Map.h"

Map::Map(int width, int height){
	this->width = width;
	this->height = height;
	
	for(int i = 0; i < height; i++){
		std::vector<unsigned int> row;
		row.resize(width);
		for(int j = 0; j < width; j++){
			row.push_back(0);
		}
		map.push_back(row);
	}
	if(!txt.loadFromFile("tilesheet.png")){
		std::cout << "ERROR" << std::endl;
	} else{
		spr.setTexture(txt);
	}
}

void Map::addTile(unsigned int id, int x, int y){
	if(x > width-1 || y > height-1){
		return;
	}
	map[x][y] = id;
}

void Map::drawMap(sf::RenderWindow& window, Tilemap tilemap){
	for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
			sf::IntRect rect(tilemap.getRectById(map[j][i]));
			spr.setPosition(j*64, i*64);
			spr.setTextureRect(rect);
			window.draw(spr);
		}
	}
}
