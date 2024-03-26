#include "pch.h"
#include "Digits.h"

Digits::Digits()
{
	digits.setTexture(TextureManager::GetTexture("digits"));
	positionsSet = false; 
}
//window gets passed in from board. 
//key will be mine count. 
void Digits::PopulateMap()
{
	//texture.loadFromFile("images/digits.png", sf::IntRect(21*5, 0, 21, 32));
	for (int i = 0; i < 11; i++) {
		//create sprite
		digits.setTextureRect(sf::IntRect(21*i, 0, 21, 32)); 
		//set position
		digits.setPosition(0, 0);

		//store with key 
		string tmp = std::to_string(i);
		if (i == 10) {
			digitMap.emplace('-', digits); 
		}
		else {
			digitMap.emplace(tmp.at(0), digits);
		}
	}
}

void Digits::DrawDigits(sf::RenderWindow & window)
{
	//for each element draw ... 
	for (int i = 0; i < currentDigits.size(); i++) {
		window.draw(currentDigits.at(i));
	}
}

void Digits::PopulateCurrentDigits(int mineCount, int& rows)
{
	string sMineCount = std::to_string(mineCount); 
	std::cout << mineCount << std::endl; 
	int i = 0; 
	//insert zero as first digit if not negative
	if (mineCount >= 0) {
		
		digitMap['0'].setPosition(digitMap['0'].getGlobalBounds().width, digitMap['0'].getGlobalBounds().height*rows);
		currentDigits.push_back(digitMap['0']);
		//if single digits add 0 in front of sMineCount : 0 9 -> 009
		if (mineCount < 100) {
			sMineCount.insert(0, "0");
			if(mineCount < 10)
				sMineCount.insert(0, "0");
		}
	}
	else if (mineCount < 0) { 
		//i--;
		if (mineCount > -10) {
			sMineCount.insert(1, "0");
			sMineCount.insert(1, "0");
		}
		else if (mineCount <= -10) {
			sMineCount.insert(1, "0");
		}
	}
	for (char tmp : sMineCount) {
		digitMap[tmp].setPosition(digitMap['0'].getGlobalBounds().width+(21*i++), digitMap['0'].getGlobalBounds().height*rows );
		currentDigits.push_back(digitMap[tmp]);
	}
	
}

