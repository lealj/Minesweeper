#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class Tile 
{
	int column; 
	int row; 
	bool mineStatus; 
	sf::Sprite defTile, revealedTile, mine, n1, n2, n3, n4, n5, n6, n7, n8, flag; 
	sf::Vector2i position; 
	bool showTile; 
	std::vector<Tile*> surroundTiles;  
	bool mineNear; 
	bool flagHere; 
	bool debugMode; 
	
public:
	//Tile(); 
	Tile(bool mineStatus); 
	void AdjustPos(int xmulti, int ymulti); 
	void SetColRow(int column, int row); 
	void FillSurroundTiles(Tile* tile); 
	void DrawTile(sf::RenderWindow& window); 
	void Reveal();
	void ShowTile(); 
	void SetFlag(); 
	void DebugMode(); 
	//access
	sf::FloatRect ReturnPosition();
	sf::FloatRect ReturnDimensions(); 
	int ReturnCol(); 
	int ReturnRow(); 
	bool GetMineStatus(); 
	bool GetFlagStatus(); 
	bool GetShowTileStatus(); 
	bool GetMineNearStatus(); 


};

