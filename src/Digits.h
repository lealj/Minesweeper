#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <iostream>
#include <string>

class Digits
{
	sf::Sprite digits;
	sf::Sprite sprite;
	bool positionsSet; 
	std::map<char, sf::Sprite> digitMap;
	std::vector<sf::Sprite> currentDigits; 
public:
	Digits();
	void PopulateMap();
	void DrawDigits(sf::RenderWindow & window); 
	void PopulateCurrentDigits(int mineCount, int& rows); 

};

