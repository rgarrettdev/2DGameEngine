#include "./Engine.h"
#include "./Map.h"
#include "./EntityManager.h"
#include <fstream> //Library of file functions.
#include "./Components/TileComponent.h"

extern EntityManager manager;
Map::Map(std::string textureID, int scale, int tileSize) {
	this->textureID = textureID;
	this->scale = scale;
	this->tileSize = tileSize;
}

void Map::LoadMap(std::string filePath, int mapSizeX, int mapSizeY) {
	//Read map tile definitions from .map file
	std::fstream mapFile;
	mapFile.open(filePath);

	for (int y = 0; y < mapSizeY; y++)
	{
		for (int x = 0; x < mapSizeX; x++)
		{
			char ch;
			mapFile.get(ch); //Gets the char from map file
			int sourceRectY = atoi(&ch) * tileSize;
			mapFile.get(ch);
			int sourceRectX = atoi(&ch) * tileSize;
			AddTile(sourceRectX, sourceRectY, x * (scale * tileSize), y * (scale * tileSize));
			mapFile.ignore();
		}
	}
	mapFile.close();
}

void Map::AddTile(int sourceX, int sourceY, int x, int y) {
	//Add new tile entity in engine
	Entity& newTile(manager.AddEntity("Tile")); //Will have serveral tiles called tile.
	newTile.AddComponent<TileComponent>(sourceX, sourceY, x, y, tileSize, scale, textureID);
}