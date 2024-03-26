#include "Tile.h"

Tile::Tile(bool mineStatus)
{
	column = 0; 
	row = 0; 
	this->mineStatus = mineStatus; 
	
	defTile.setTexture(TextureManager::GetTexture("tile_hidden"));
	revealedTile.setTexture(TextureManager::GetTexture("tile_revealed"));
	mine.setTexture(TextureManager::GetTexture("mine"));
	flag.setTexture(TextureManager::GetTexture("flag")); 

	n1.setTexture(TextureManager::GetTexture("number_1")); 
	n2.setTexture(TextureManager::GetTexture("number_2"));
	n3.setTexture(TextureManager::GetTexture("number_3"));
	n4.setTexture(TextureManager::GetTexture("number_4"));
	n5.setTexture(TextureManager::GetTexture("number_5"));
	n6.setTexture(TextureManager::GetTexture("number_6"));
	n7.setTexture(TextureManager::GetTexture("number_7"));
	n8.setTexture(TextureManager::GetTexture("number_8"));
	showTile = false; 
	mineNear = false; 
	flagHere = false; 
	debugMode = false; 
}

void Tile::AdjustPos(int xmulti, int ymulti)
{
	//moves tiles to the left/down by the distance of (multiplier * tile width/height)
	defTile.setPosition(defTile.getLocalBounds().width * xmulti, defTile.getLocalBounds().height * ymulti);
	revealedTile.setPosition(defTile.getLocalBounds().width * xmulti, defTile.getLocalBounds().height * ymulti);
	mine.setPosition(defTile.getLocalBounds().width * xmulti, defTile.getLocalBounds().height * ymulti);
	flag.setPosition(defTile.getLocalBounds().width * xmulti, defTile.getLocalBounds().height * ymulti);

	n1.setPosition(defTile.getLocalBounds().width * xmulti, defTile.getLocalBounds().height * ymulti);
	n2.setPosition(defTile.getLocalBounds().width * xmulti, defTile.getLocalBounds().height * ymulti);
	n3.setPosition(defTile.getLocalBounds().width * xmulti, defTile.getLocalBounds().height * ymulti);
	n4.setPosition(defTile.getLocalBounds().width * xmulti, defTile.getLocalBounds().height * ymulti);
	n5.setPosition(defTile.getLocalBounds().width * xmulti, defTile.getLocalBounds().height * ymulti);
	n6.setPosition(defTile.getLocalBounds().width * xmulti, defTile.getLocalBounds().height * ymulti);
	n7.setPosition(defTile.getLocalBounds().width * xmulti, defTile.getLocalBounds().height * ymulti);
	n8.setPosition(defTile.getLocalBounds().width * xmulti, defTile.getLocalBounds().height * ymulti);
}

void Tile::DrawTile(sf::RenderWindow& window) {
	//if tile is marked to be revealed (from being clicked on earlier), draw revealed tile 
	if (showTile) {
		window.draw(revealedTile);
		if (mineStatus) {
			if (flagHere)
				window.draw(flag);

			window.draw(mine);
		}
		else {
			//if mine in radius
			int mineCount = 0;
			for (unsigned int i = 0; i < surroundTiles.size(); i++) {
				if (surroundTiles.at(i)->GetMineStatus()) {
					mineCount++;
				}
			}
			if (mineCount == 1)
				window.draw(n1);
			else if (mineCount == 2)
				window.draw(n2);
			else if (mineCount == 3)
				window.draw(n3);
			else if (mineCount == 4)
				window.draw(n4);
			else if (mineCount == 5)
				window.draw(n5);
			else if (mineCount == 6)
				window.draw(n6);
			else if (mineCount == 7)
				window.draw(n7);
			else if (mineCount == 8)
				window.draw(n8);
		}
	}
	else {
		window.draw(defTile);
		if (flagHere)
			window.draw(flag); 
		if (debugMode)
			window.draw(mine); 
	}
}

void Tile::Reveal()
{
	if (!showTile && !flagHere) {
		showTile = true;
		if (!mineNear) {
			for (unsigned int i = 0; i < surroundTiles.size(); i++) {
				if (!surroundTiles.at(i)->mineStatus)
					surroundTiles.at(i)->Reveal();
			}
		}
	}
	
}

sf::FloatRect Tile::ReturnPosition()
{
	return defTile.getGlobalBounds();
}

void Tile::SetColRow(int column, int row)
{
	this->column = column; 
	this->row = row; 
}

void Tile::FillSurroundTiles(Tile* tile)
{
	if (tile->GetMineStatus()) {
		mineNear = true;
	}
	surroundTiles.push_back(tile); 
}

bool Tile::GetMineStatus()
{
	return mineStatus; 
}

void Tile::ShowTile()
{
	showTile = true; 
}

int Tile::ReturnCol()
{
	return column;
}

void Tile::SetFlag()
{
	flagHere = !flagHere; 
}

int Tile::ReturnRow()
{
	return row; 
}

void Tile::DebugMode()
{
	debugMode = !debugMode;
}

sf::FloatRect Tile::ReturnDimensions()
{
	return defTile.getLocalBounds();
}

bool Tile::GetFlagStatus()
{
	return flagHere;
}

bool Tile::GetShowTileStatus()
{
	return showTile; 
}

bool Tile::GetMineNearStatus()
{
	return mineNear; 
}



