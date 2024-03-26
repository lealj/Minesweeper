#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class Counter
{
	sf::Sprite digitsImage; 
	std::vector<sf::Vector2i> positions;
	std::vector<sf::Sprite> individualDigits; 
	std::vector<sf::Sprite> displayDigits; 
	sf::FloatRect tileRefRect; 
	int tileRows; 
	int mines; 
public:
	Counter(); 
	void DrawCounter(sf::RenderWindow& window); 
	void FillSpriteVector(); 
	void GetTileRowCount(int rows); 
	void GetTotalMines(int mines); 
	void UpdateCount(); 
	void SubtractMines(); 
	void AddMines(); 
	void SetCounterZero(); 
};

