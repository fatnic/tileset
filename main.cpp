#include <SFML/Graphics.hpp>
#include <math.h>
#include <string>
#include <sstream>
#include <iostream>

sf::Vector2i mainWindow(800,600);

int main()
{
    sf::RenderWindow window;

    sf::Image imgTileset;
    imgTileset.loadFromFile("assets/test_tiles.png");

    int tileWidth = 32;
    int tileHeight = 32;

    int tilesX = imgTileset.getSize().x / tileWidth; //3

    int screenXTiles = 3;
    int screenYTiles = 3;

    window.create(sf::VideoMode(tileWidth * screenXTiles, tileHeight * screenYTiles), "GameWindow");

    std::string map = "1,2,3,4,5,6,7,8,9";
    std::istringstream ss(map);
    std::string tile;

    sf::Texture mapTexture;
    mapTexture.create(tileWidth * screenXTiles, tileHeight * screenYTiles);

    int tilePosX = 1;
    int tilePosY = 1;

    while(std::getline(ss, tile, ','))
      {

        sf::Image imgTile;
        imgTile.create(tileWidth, tileHeight);

        int startX = ((std::stoi(tile)-1) % tilesX) * tileWidth;
        int startY = ((std::stoi(tile)-1) / tilesX) * tileHeight;

        imgTile.copy(imgTileset, 0, 0, sf::IntRect(startX, startY, tileWidth, tileHeight), false);

        mapTexture.update(imgTile, (tilePosX * tileWidth) - tileWidth, (tilePosY * tileHeight) - tileHeight);

        if (tilePosX == screenXTiles) { tilePosY++; tilePosX = 0; }

        tilePosX++;

      }

    sf::Sprite background(mapTexture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(background);
        window.display();
    }

    return 0;
}
