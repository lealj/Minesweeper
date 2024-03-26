#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class MiscButtons
{
	//Misc Buttons  
	sf::Sprite happy;
	sf::Sprite happyDead; 
	sf::Sprite happyCool; 
	sf::Sprite debug;
	sf::Sprite test1;
	sf::Sprite test2;
	sf::Sprite test3;
	sf::Vector2i position; 

	bool gameIsOver, restartGame, wonGame, debugMode, testMode; 

public:
	MiscButtons();

	void Draw(sf::RenderWindow& window, int index);
	void SetPosition(float x, float y, int index);
	void ClickHappened(int mouseX, int mouseY);
	int GetWidth();
	int GetHeight();
	void GameOver(); 
	bool GetRestartGameStatus(); 
	bool GetDebugStatus(); 
	bool GetTestStatus(); 
	void WonGame(); 
};

