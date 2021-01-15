#include "Tilemap.h"

Tilemap::Tilemap(std::string fileName, int gridWidth, int gridHeight){
	this->gridWidth = gridWidth;
	this->gridHeight = gridHeight;
	if(!this->texture.loadFromFile(fileName)){
		std::cout << "Could not load file: " << fileName << std::endl;
	}
	this->sprite.setTexture(this->texture);

	this->initTiles();

}

void Tilemap::drawTiles(sf::RenderWindow* window){
	for(int y = 0; y < tiles.size(); y++){
		for(int x = 0; x < tiles[0].size(); x++){
			this->sprite.setTextureRect(this->tiles[y][x]->rect);
			this->sprite.setPosition(this->tiles[y][x]->rect.left, this->tiles[y][x]->rect.top);
			window->draw(sprite);
		}
	}
}

void Tilemap::initTiles(){
	unsigned int w = this->texture.getSize().x / gridWidth;
	unsigned int h = this->texture.getSize().y / gridHeight;
	unsigned int id = 0;
	for(int y = 0; y < h; y++){
		std::vector<Tile*> *row = new std::vector<Tile*>;
		for(int x = 0; x < w; x++, id++){
			sf::IntRect tileRect(x*gridWidth, y*gridHeight, gridWidth, gridHeight);
			Tile* tile = new Tile(id, tileRect);
			row->push_back(tile);
			std::cout << "id: " << tile->id << "\t" << tile->rect.left << " " << tile->rect.top << " " << tile->rect.width << " " << tile->rect.height << std::endl;
		}
		this->tiles.push_back(*row);
		this->tiles.size();
	}
}

sf::Vector2u Tilemap::getTilemapSize(){
	return this->texture.getSize();
}

sf::IntRect Tilemap::getRectById(unsigned int id){
	for(int y = 0; y < this->tiles.size(); y++){
		for(int x = 0; x < this->tiles[0].size(); x++){
			if(this->tiles[y][x]->id== id){
				return this->tiles[y][x]->rect;
			}
		}
	}
	return sf::IntRect();
}
