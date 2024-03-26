#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Random.h"
#include "TextureManager.h"
#include "Board.h"

using namespace std;
//sf::Sprite spaceSprite(TextureManager::GetTexture("space")); 

//Main(get dimensions from board file) -> board -> tiles

/* TODO */
/*
    window size if small amount of tiles 
    mine count messed up
*/

int main()
{
    Board board;
    board.ReadConfig(); 

    board.ReadTestBoard(0); 

    //reference textures for window size
    sf::Sprite tileRef;
    tileRef.setTexture(TextureManager::GetTexture("tile_hidden"));
    sf::Sprite smileyRef; 
    smileyRef.setTexture(TextureManager::GetTexture("face_happy"));

    int width = tileRef.getLocalBounds().width * board.GetXTileCount();
    int height = (tileRef.getLocalBounds().height * board.GetYTileCount()) + smileyRef.getLocalBounds().height;
   
    sf::RenderWindow window(sf::VideoMode(width,height), "SFML works!");
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                
                if (event.mouseButton.button == sf::Mouse::Left) {
                    board.LeftClick(mousePosition.x, mousePosition.y); 
                    if (board.GetResetStatus()) {
                        //reset game
                        int testNumb = board.GetTestQue(); 
                        board = Board::Board(); 
                        board.ReadConfig(); 
                        board.ReadTestBoard(testNumb);
                    }
                }
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    board.RightClick(mousePosition.x, mousePosition.y);
                }
            }
        }
        board.CheckWin();
        window.clear();
        board.DrawBoard(window);
        window.display();
    }

    TextureManager::Clear(); 
    
    return 0;
}
