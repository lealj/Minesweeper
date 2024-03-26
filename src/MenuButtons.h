#pragma once
#include "Tile.h"
#include <SFML/Graphics.hpp>
#include <vector>
class MenuButtons
{
	sf::Sprite face, test1, test2, test3, debug; 
	sf::Vector2i position; 
public:
	MenuButtons(); 
	void AdjustPos(int multi, int xtileCount, int ytileCount);
	void DrawButtons(sf::RenderWindow& window, int index);
	void ChangeFace(int faceType); 
	sf::FloatRect ReturnPosition(int index);
	void Clicked(int index); 
};

