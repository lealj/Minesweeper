#include "pch.h"
#include "MiscButtons.h"
#include <iostream>

MiscButtons::MiscButtons()
{
	happy.setTexture(TextureManager::GetTexture("face_happy"));
	happyDead.setTexture(TextureManager::GetTexture("face_lose"));
	happyCool.setTexture(TextureManager::GetTexture("face_win"));
	debug.setTexture(TextureManager::GetTexture("debug"));
	test1.setTexture(TextureManager::GetTexture("test_1"));
	test2.setTexture(TextureManager::GetTexture("test_2"));
	test3.setTexture(TextureManager::GetTexture("test_3"));

	gameIsOver = false; 
	restartGame = false; 
	wonGame = false;
	debugMode = false; 
	testMode = false; 
}

void MiscButtons::Draw(sf::RenderWindow & window, int index)
{
	if (index == 0) {
		if (!gameIsOver)
			window.draw(happy);
		else if (wonGame && gameIsOver) {
			window.draw(happyCool); 
		}
		else if (gameIsOver)
			window.draw(happyDead); 
	}
	if (index == 1) {
		window.draw(debug);
	}
	if (index == 2)
		window.draw(test1);
	if (index == 3)
		window.draw(test2);
	if (index == 4)
		window.draw(test3);
}

void MiscButtons::SetPosition(float x, float y, int index)
{
	position.x = x;
	position.y = y;

	if (index == 0) {
		happy.setPosition(x, y);
		happyDead.setPosition(x, y);
		happyCool.setPosition(x, y); 
	}
	if (index == 1)
		debug.setPosition(x, y); 
	if (index == 2)
		test1.setPosition(x, y);
	if (index == 3)
		test2.setPosition(x, y);
	if (index == 4)
		test3.setPosition(x, y);

}

void MiscButtons::ClickHappened(int mouseX, int mouseY)
{
	if (happyDead.getGlobalBounds().contains(mouseX, mouseY) && gameIsOver) {
		restartGame = true; 
	}
	else if (debug.getGlobalBounds().contains(mouseX, mouseY)) {
		debugMode = !debugMode;
	}
	else if (test1.getGlobalBounds().contains(mouseX, mouseY)) {
		testMode = true;
	}
	else if (test2.getGlobalBounds().contains(mouseX, mouseY)) {
		testMode = true;
	}
	else if (test3.getGlobalBounds().contains(mouseX, mouseY)) {
		testMode = true;
	}

}

int MiscButtons::GetWidth()
{
	return happy.getLocalBounds().width;
}

int MiscButtons::GetHeight()
{
	return happy.getLocalBounds().height;
}

void MiscButtons::GameOver()
{
	gameIsOver = true; 
}

bool MiscButtons::GetRestartGameStatus()
{
	return restartGame; 
}

bool MiscButtons::GetDebugStatus() {
	return debugMode; 
}

bool MiscButtons::GetTestStatus() {
	return testMode; 
}
void MiscButtons::WonGame()
{
	wonGame = true; 
}
/*
void MiscButtons::WonGame() {
	wonGame = true;
	gameIsOver = true;
}
*/



