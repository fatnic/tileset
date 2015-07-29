#include <SFML/Graphics.hpp>
#include <math.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "pugixml.hpp"

int main()
{
    sf::RenderWindow window;

    // read map file
    pugi::xml_document mapDoc;
    mapDoc.load_file("assets/map2.tmx");

    pugi::xml_node nodeMap = mapDoc.child("map");
    pugi::xml_node nodeTileset = mapDoc.child("map").child("tileset");
    pugi::xml_node nodeData = mapDoc.child("map").child("layer").child("data");

    sf::Image imgTileset;

    std::string fnTileset = nodeTileset.child("image").attribute("source").as_string();

    imgTileset.loadFromFile("assets/" + fnTileset);

    // width/height of each tile
    int tileWidth = nodeTileset.attribute("tilewidth").as_int();
    int tileHeight = nodeTileset.attribute("tileheight").as_int();

    // Amount of tiles per row
    int tilesX = imgTileset.getSize().x / tileWidth; //3

    // Amount of tiles per screen x/y
    int screenXTiles = nodeMap.attribute("width").as_int();
    int screenYTiles = nodeMap.attribute("height").as_int();

    window.create(sf::VideoMode(tileWidth * screenXTiles, tileHeight * screenYTiles), "GameWindow");

    // create new texture for placing tiles
    sf::Texture mapTexture;
    mapTexture.create(tileWidth * screenXTiles, tileHeight * screenYTiles);

    // initial grid position
    int tilePosX = 1;
    int tilePosY = 1;

    // grab csv of map tile numbers and parse
    std::string rawstring = nodeData.child_value();
    rawstring.erase(std::remove(rawstring.begin(), rawstring.end(), '\n'), rawstring.end());
    std::string map = rawstring.c_str();
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
