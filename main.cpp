#include <SFML/Graphics.hpp>
#include <math.h>
#include <string>
#include <sstream>
#include <iostream>

sf::Vector2i mainWindow(800,600);

int main()
{
    sf::RenderWindow window;

    // Load tileset image into memory
    sf::Image imgTileset;
    imgTileset.loadFromFile("assets/test_tiles.png");

    // width/height of each tile
    int tileWidth = 32;
    int tileHeight = 32;

    // Amount of tiles per row
    int tilesX = imgTileset.getSize().x / tileWidth; //3

    // Amount of tiles per screen x/y
    int screenXTiles = 3;
    int screenYTiles = 3;

    window.create(sf::VideoMode(tileWidth * screenXTiles, tileHeight * screenYTiles), "GameWindow");

    // create new texture for placing tiles
    sf::Texture mapTexture;
    mapTexture.create(tileWidth * screenXTiles, tileHeight * screenYTiles);

    // initial grid position
    int tilePosX = 1;
    int tilePosY = 1;

    // grab csv of map tile numbers and parse
    std::string map = "1,2,3,4,5,6,7,8,9";
    std::istringstream ss(map);
    std::string tile;

    while(std::getline(ss, tile, ','))
      {

        // new image to place current tile
        sf::Image imgTile;
        imgTile.create(tileWidth, tileHeight);

        // starting x/y of selected tile
        int startX = ((std::stoi(tile)-1) % tilesX) * tileWidth;
        int startY = ((std::stoi(tile)-1) / tilesX) * tileHeight;

        // paste selected tile into blank image
        imgTile.copy(imgTileset, 0, 0, sf::IntRect(startX, startY, tileWidth, tileHeight), false);
        // paste image onto texture
        mapTexture.update(imgTile, (tilePosX * tileWidth) - tileWidth, (tilePosY * tileHeight) - tileHeight);

        // if reached the end of a row go to next
        if (tilePosX == screenXTiles) { tilePosY++; tilePosX = 0; }
        tilePosX++;

      }

    // stick completed texture onto final sprite for rendering
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
