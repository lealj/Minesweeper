#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Tile.h"
#include "MenuButtons.h"
#include "Random.h"
#include "Counter.h"
#include <SFML/Graphics.hpp>

using namespace std; 

class Board
{
	//board needs x,y coords for tiles amounts. 
	unsigned int xtileCount; 
	unsigned int ytileCount; 
	int totalMines;
	int mineCount; 
	bool testStatus; 
	vector<Tile> tiles;
	vector<MenuButtons> menuButtons;
	bool gameOver; 
	bool resetGame; 
	bool gameLost;
	bool queTest1; 
	bool queTest2;
	bool queTest3;
	Counter counter; 
public: 
	Board(); 
	void ReadConfig(); 
	void ReadTestBoard(int testVers);
	void DrawBoard(sf::RenderWindow& window); 
	void PopulateTiles(vector<string>& testLayout); 
	void LeftClick(int x_mousePosition, int y_mousePosition);
	void RightClick(int x_mousePosition, int y_mousePosition);
	void RevealAll(); 
	void CheckWin(); 
	//access
	unsigned int GetXTileCount(); 
	unsigned int GetYTileCount();
	bool GetResetStatus(); 
	unsigned int GetTestQue(); 
};

