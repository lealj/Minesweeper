#include "Counter.h"

void Counter::FillSpriteVector()
{
	//settings sprites as crops of original image. 
	for (unsigned int i = 0; i < 11; i++) {
		//set = to original
		sf::Sprite sprite = digitsImage;
		//modify rect to only take one piece of image
		sf::IntRect intRect;
		intRect.left = (digitsImage.getLocalBounds().width / 11) * i; 
		intRect.height = digitsImage.getLocalBounds().height;
		intRect.width = (digitsImage.getLocalBounds().width)/ 11;
		
		sprite.setTextureRect(intRect);
		sprite.setPosition(0, 32 * tileRows);

		individualDigits.push_back(sprite);
		//positions : 1234
		
		if (i < 4) {
			sf::Vector2i vect2i;
			vect2i.x = intRect.left;
			vect2i.y = 32*tileRows;
			positions.push_back(vect2i);
		}
	}
	individualDigits.at(10).setPosition(positions.at(0).x, positions.at(0).y);
}

Counter::Counter()
{
	digitsImage.setTexture(TextureManager::GetTexture("digits"));
	tileRows = 0; 
	mines = 0;
}

void Counter::DrawCounter(sf::RenderWindow& window)
{
	for(unsigned int i = 0; i < 3; i++)
		window.draw(displayDigits.at(i));
	if(mines < 0)
		window.draw(individualDigits.at(10)); 
}

void Counter::GetTileRowCount(int rows)
{
	tileRows = rows;
}

void Counter::GetTotalMines(int mines)
{
	this->mines = mines; 
}

void Counter::UpdateCount()
{
	displayDigits.clear(); 
	
	string mineCount = std::to_string(mines);
	if (mineCount.at(0) == '-') {
		mineCount.erase(0,1);
	}
	if (mineCount.length() == 1) {
		mineCount.insert(0, "00");
	}
	else if (mineCount.length() == 2) {
		mineCount.insert(0, "0");
	}
	//50 -> '0' '5' '0'
	for (unsigned int i = 0; i < 3; i++) {
		displayDigits.push_back(individualDigits.at((int)mineCount.at(i) - 48));
		displayDigits.at(i).setPosition(positions.at(i + 1).x, positions.at(i + 1).y);
	}
}

void Counter::SubtractMines()
{
	mines--; 
}

void Counter::AddMines()
{
	mines++; 
}

void Counter::SetCounterZero()
{
	mines = 0; 
}




