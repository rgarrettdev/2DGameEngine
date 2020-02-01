#ifndef MAP_H
#define MAP_H

class Map
{
public:
	Map(std::string textureID, int scale, int tileSize);
	~Map();
	void LoadMap(std::string filePath, int mapSizeX, int mapSizeY);
	void AddTile(int sourceX, int sourceY, int x, int y);

private:
	std::string textureID;
	int scale;
	int tileSize; //Assume tiles are square!
};

#endif // !MAP_H

