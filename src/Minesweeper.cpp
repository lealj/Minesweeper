#include "pch.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Random.h"
#include "TextureManager.h"
#include "Board.h"
#include "Tile.h"
using namespace std;

/* Tasks
 To Do: 
	Test Boards

	Digits Screw up when placing then removing... 
	Happy cool face if win
*/

int main() {

	Board board;
	//reference sprites
	sf::Sprite htileSprite(TextureManager::GetTexture("tile_hidden"));
	sf::Sprite happyface(TextureManager::GetTexture("face_happy"));
	//window size
	int xwindow = htileSprite.getLocalBounds().width * board.GetCols();
	int ywindow = htileSprite.getLocalBounds().height * board.GetRows() + happyface.getLocalBounds().height;

	sf::RenderWindow window(sf::VideoMode(xwindow, ywindow), "Minesweeper");

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			//User input
			if (event.type == sf::Event::MouseButtonPressed) {
				//reveal tile - if mine end game
				if (event.mouseButton.button == sf::Mouse::Left) {

					sf::Vector2i mousePos = sf::Mouse::getPosition(window); 
					board.ClickHappened(mousePos.x, mousePos.y); 
					
					if (board.GetMiscButtonCopy().GetRestartGameStatus()) {
						board = Board::Board(); 
						break; 
					}
					if (board.GetTest1Status()) {
						//button working instantly :)
						string testFile = "boards/testboard1.brd"; 
						board = Board::Board(1, testFile); 

					}
					else if (board.GetTest2Status()) {
						string testFile = "boards/testboard2.brd";
						board = Board::Board(2, testFile);
					}
					else if (board.GetTest3Status()) {
						string testFile = "boards/testboard3.brd";
						board = Board::Board(3, testFile);
					}
					
				}
				if (event.mouseButton.button == sf::Mouse::Right) {
					sf::Vector2i mousePos = sf::Mouse::getPosition(window);
					board.RightClickHappened(mousePos.x, mousePos.y);
				}
			}
		}
	
		window.clear();	//clear previous screen 
		//Drawing
		board.Draw(window); 
	
		window.display(); //presents everyting to monitor
	}
	TextureManager::Clear();
	return 0; 
}

	

