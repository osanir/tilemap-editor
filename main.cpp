#include <SFML/Graphics.hpp>
#include "Tilemap.h"
#include "Map.h"

const int GRID_WIDTH = 64;
const int GRID_HEIGHT = 64;
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

enum class ViewMode{
    Edit,
    Select
};

int main(){
    Tilemap tilemap("tilesheet.png", GRID_WIDTH, GRID_HEIGHT);
    Map map(20, 20);
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
    sf::RectangleShape selectionBox;
    ViewMode mode = ViewMode::Select;
    sf::View view;

    view.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    float zoomScale = (float)tilemap.getTilemapSize().x / (float)WINDOW_WIDTH;
    view.setCenter(sf::Vector2f(tilemap.getTilemapSize().x / 2.f, (WINDOW_HEIGHT / 2.f) * zoomScale));
    view.zoom(zoomScale);
    //view.setCenter(sf::Vector2f(0,0));
    //(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));

    window.setView(view);

    selectionBox.setSize(sf::Vector2f(GRID_WIDTH, GRID_HEIGHT));
    selectionBox.setFillColor(sf::Color::Transparent);
    selectionBox.setOutlineColor(sf::Color::Red);
    selectionBox.setOutlineThickness(4);

    unsigned int currentId = 0;
    unsigned int selectedId = 0;
    bool selecting = false;

    sf::Vector2f position(0,0);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed){
                window.close();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
                mode = ViewMode::Edit;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                mode = ViewMode::Select;
            }
            if(mode == ViewMode::Select){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                    selecting = true;
                    selectedId = currentId;
                    std::cout << selectedId << std::endl;
                }
                if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space){
                    selecting = false;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                    if(selectionBox.getPosition().x - GRID_WIDTH >= 0){
                        selectionBox.move(sf::Vector2f(-GRID_WIDTH, 0));
                        currentId--;
                    }
                    std::cout << currentId << std::endl;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                    if(selectionBox.getPosition().x + GRID_WIDTH < tilemap.getTilemapSize().x){
                        selectionBox.move(sf::Vector2f(GRID_WIDTH, 0));
                        currentId++;
                    }
                    std::cout << currentId << std::endl;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                    if(selectionBox.getPosition().y - GRID_HEIGHT >= 0){
                        selectionBox.move(sf::Vector2f(0, -GRID_HEIGHT));
                        currentId -= tilemap.getTilemapSize().x / GRID_HEIGHT ;
                        //std::cout << view.getCenter().y - view.getSize().y / 2.f << " < " << selectionBox.getPosition().y << std::endl;
                        if(view.getCenter().y - view.getSize().y / 2.f > selectionBox.getPosition().y){
                            view.move(0, -64);
                        }
                    }
                    std::cout << currentId << std::endl;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                    if(selectionBox.getPosition().y + GRID_HEIGHT < tilemap.getTilemapSize().y){
                        selectionBox.move(sf::Vector2f(0, GRID_HEIGHT));
                        currentId += tilemap.getTilemapSize().x / GRID_HEIGHT;
                        //std::cout << view.getCenter().y + view.getSize().y / 2.f << " < " << selectionBox.getPosition().y + GRID_HEIGHT << std::endl;
                        if(view.getCenter().y + view.getSize().y / 2.f < selectionBox.getPosition().y + GRID_HEIGHT){
                            view.move(0, 64);
                        }
                    
                    }
                    std::cout << currentId << std::endl;
                }
            } else if(mode == ViewMode::Edit){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                    map.addTile(selectedId, position.x, position.y);
                    std::cout << selectedId << " " << position.x << " " << position.y << std::endl;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                    if(selectionBox.getPosition().x - GRID_WIDTH >= 0){
                        selectionBox.move(sf::Vector2f(-GRID_WIDTH, 0));
                        currentId--;
                    }
                    std::cout << currentId << std::endl;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                    if(selectionBox.getPosition().x + GRID_WIDTH < tilemap.getTilemapSize().x){
                        selectionBox.move(sf::Vector2f(GRID_WIDTH, 0));
                        currentId++;
                    }
                    std::cout << currentId << std::endl;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                    if(selectionBox.getPosition().y - GRID_HEIGHT >= 0){
                        selectionBox.move(sf::Vector2f(0, -GRID_HEIGHT));
                        currentId -= tilemap.getTilemapSize().x / GRID_HEIGHT;
                        //std::cout << view.getCenter().y - view.getSize().y / 2.f << " < " << selectionBox.getPosition().y << std::endl;
                        if(view.getCenter().y - view.getSize().y / 2.f > selectionBox.getPosition().y){
                            view.move(0, -64);
                        }
                    }
                    std::cout << currentId << std::endl;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                    if(selectionBox.getPosition().y + GRID_HEIGHT < tilemap.getTilemapSize().y){
                        selectionBox.move(sf::Vector2f(0, GRID_HEIGHT));
                        currentId += tilemap.getTilemapSize().x / GRID_HEIGHT;
                        //std::cout << view.getCenter().y + view.getSize().y / 2.f << " < " << selectionBox.getPosition().y + GRID_HEIGHT << std::endl;
                        if(view.getCenter().y + view.getSize().y / 2.f < selectionBox.getPosition().y + GRID_HEIGHT){
                            view.move(0, 64);
                        }

                    }
                    std::cout << currentId << std::endl;
                }
            }
            
        }

        if(selecting){
            selectionBox.setOutlineColor(sf::Color::Blue);
        } else{
            selectionBox.setOutlineColor(sf::Color::Red);
        }
        position.x = selectionBox.getPosition().x / GRID_WIDTH;
        position.y = selectionBox.getPosition().y / GRID_HEIGHT;

        window.setView(view);
        window.clear();
        if(mode == ViewMode::Edit){
            map.drawMap(window, tilemap);

        } else if(mode == ViewMode::Select){
            tilemap.drawTiles(&window);

        }
        window.draw(selectionBox);
        window.display();

    }

    return 0;
}