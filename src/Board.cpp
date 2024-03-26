#include "Board.h"


Board::Board()
{
	xtileCount = 0; 
	ytileCount = 0; 
	totalMines = 0; 
	mineCount = 0; 
	testStatus = false; 
	gameOver = false; 
	resetGame = false; 
	gameLost = false; 
	queTest1 = false; 
	queTest2 = false; 
	queTest3 = false; 
}

void Board::ReadConfig()
{
	ifstream file("boards/config.cfg"); 
	string tmp = ""; 
	//x
	getline(file, tmp); 
	xtileCount = stoi(tmp); 
	//y
	getline(file, tmp);
	ytileCount = stoi(tmp);
	//mines
	getline(file, tmp);
	totalMines = stoi(tmp);
	
	counter.GetTileRowCount(ytileCount);
	counter.GetTotalMines(totalMines); 
}

void Board::ReadTestBoard(int testVers)
{
	vector<string> testLayout;
	//string of each row
	string tmp = "";

	if (testVers != 0) {
		testStatus = true;
		string testName = "boards/testboard";
		testName += to_string(testVers);
		testName += ".brd";

		fstream file(testName);

		while (getline(file, tmp)) {
			testLayout.push_back(tmp);
		}
	}
	else {
		//create empty board (0's)
		for (unsigned int i = 0; i < ytileCount; i++) {
			tmp = ""; 
			for (unsigned int j = 0; j < xtileCount; j++) {
				tmp += "0"; 
			}
			testLayout.push_back(tmp); 
		}
		//set mines
		int minesCopy = totalMines; 
		while (minesCopy > 0) {
			for (unsigned int i = 0; i < testLayout.size(); i++) {
				for (unsigned int j = 0; j < testLayout.at(i).length(); j++) {
					if (Random::Number(1, xtileCount) == 1 && minesCopy >0) {
						testLayout.at(i).at(j) = '1';
						minesCopy--; 
					}
				}
			}
		}
	}
	PopulateTiles(testLayout); 
}

void Board::DrawBoard(sf::RenderWindow& window)
{
	for (unsigned int i = 0; i < tiles.size(); i++) {
		tiles.at(i).DrawTile(window); 
	}

	for(unsigned int i = 0; i < menuButtons.size(); i++)
		menuButtons.at(i).DrawButtons(window, i); 
	
	counter.DrawCounter(window); 
}

void Board::PopulateTiles(vector<string>& testLayout)
{
	ytileCount = testLayout.size(); 
	xtileCount = testLayout.at(0).length(); 
	// i = column, j = row
	for (unsigned int i = 0; i < testLayout.size(); i++) {
		for (unsigned int j = 0; j < testLayout.at(i).length(); j++) {
			bool mineStat = false;
			if (testLayout.at(i).at(j) == '1') {
				mineStat = true;
				mineCount++; 
			}

			Tile tile(mineStat); 
			tile.AdjustPos(j, i); 
			tile.SetColRow(i+1, j+1);
			tiles.push_back(tile); 
		}
	}

	if(testStatus)
		counter.GetTotalMines(mineCount); 
	
	//fill tile vector for surrounding tiles (top left - > top right -> left -> right -> bot left ->bot right )
	for (unsigned int i = 0; i < tiles.size(); i++) {
		//i = base tile
		for (unsigned int j = 0; j < tiles.size(); j++) {
			//if above
			if (tiles.at(j).ReturnRow() == tiles.at(i).ReturnRow() -1) {
				//top left
				if (tiles.at(j).ReturnCol() == tiles.at(i).ReturnCol() - 1) {
					tiles.at(i).FillSurroundTiles(&tiles.at(j));
				}
				//top
				if (tiles.at(j).ReturnCol() == tiles.at(i).ReturnCol()) 
					tiles.at(i).FillSurroundTiles(&tiles.at(j));
				//top right
				if (tiles.at(j).ReturnCol() == tiles.at(i).ReturnCol() + 1)
					tiles.at(i).FillSurroundTiles(&tiles.at(j));
			}
			//if next to 
			if (tiles.at(j).ReturnRow() == tiles.at(i).ReturnRow()) {
				//left
				if (tiles.at(j).ReturnCol() == tiles.at(i).ReturnCol() - 1) {
					tiles.at(i).FillSurroundTiles(&tiles.at(j));
				}
				//right
				if (tiles.at(j).ReturnCol() == tiles.at(i).ReturnCol() + 1)
					tiles.at(i).FillSurroundTiles(&tiles.at(j));
			}
			//if under
			if (tiles.at(j).ReturnRow() == tiles.at(i).ReturnRow() + 1) {
				//bottom left 
				if(tiles.at(j).ReturnCol() == tiles.at(i).ReturnCol() - 1)
					tiles.at(i).FillSurroundTiles(&tiles.at(j));
				//bottom
				if(tiles.at(j).ReturnCol() == tiles.at(i).ReturnCol())
					tiles.at(i).FillSurroundTiles(&tiles.at(j));
				//botom right 
				if(tiles.at(j).ReturnCol() == tiles.at(i).ReturnCol() + 1)
					tiles.at(i).FillSurroundTiles(&tiles.at(j));
			}
		}
	}
	//Menu buttons 
	for (unsigned int k = 0; k < 5; k++) {
		MenuButtons button; 
		button.AdjustPos(k+1, xtileCount, ytileCount); 
		menuButtons.push_back(button); 
	}
	//Counter
	counter.FillSpriteVector(); 
	counter.UpdateCount(); 
}

void Board::LeftClick(int x_mousePosition, int y_mousePosition)
{
	for (unsigned int i = 0; i < menuButtons.size(); i++) {
		if (menuButtons.at(i).ReturnPosition(i).contains(x_mousePosition, y_mousePosition)) {
			if (i == 0) {
				resetGame = true; 
			}
			//test1
			else if (i == 1) {
				queTest1 = true;
				resetGame = true; 
			}
			else if (i == 2) {
				queTest2 = true;
				resetGame = true; 
			}
			else if (i == 3) {
				queTest3 = true;
				resetGame = true; 
			}
			//debug mode 
			else if (i == 4) {
				if (!gameOver) {
					for (unsigned int i = 0; i < tiles.size(); i++) {
						if (tiles.at(i).GetMineStatus())
							tiles.at(i).DebugMode();
					}
				}
			}
		}
	}
	if (!gameOver) {
		for (unsigned int i = 0; i < tiles.size(); i++) {
			if (!tiles.at(i).GetFlagStatus()) {
				if (tiles.at(i).ReturnPosition().contains(x_mousePosition, y_mousePosition)) {
					tiles.at(i).Reveal();
					if (tiles.at(i).GetMineStatus()) {
						//game lost 
						RevealAll();
						gameOver = true; 
						gameLost = true; 
						menuButtons.at(0).ChangeFace(0); 
					}
				}
			}
		}
	}
	if (gameOver) {
		if (menuButtons.at(0).ReturnPosition(0).contains(x_mousePosition, y_mousePosition)) {
			resetGame = true;
		}
	}
}

void Board::RightClick(int x_mousePosition, int y_mousePosition)
{
	if (!gameOver) {
		for (unsigned int i = 0; i < tiles.size(); i++) {
			if (tiles.at(i).ReturnPosition().contains(x_mousePosition, y_mousePosition)) {
				if (!tiles.at(i).GetShowTileStatus()) {
					tiles.at(i).SetFlag();

					if (tiles.at(i).GetFlagStatus())
						counter.SubtractMines();
					else
						counter.AddMines();

					counter.UpdateCount();
				}
			}
		}
	}
}

void Board::RevealAll()
{
	for (unsigned int i = 0; i < tiles.size(); i++) {
		tiles.at(i).ShowTile();
	}
}

void Board::CheckWin()
{
	int revealedTiles = 0; 
	for (unsigned int i = 0; i < tiles.size(); i++) {
		//if not mine
		if (!tiles.at(i).GetMineStatus()) {
			//if shown
			if (tiles.at(i).GetShowTileStatus()) {
				revealedTiles++; 
			}
		}
	}
	if (revealedTiles == (xtileCount * ytileCount) - mineCount) {
		if (!gameLost) {
			//game won
			for (unsigned int i = 0; i < tiles.size(); i++) {
				if (tiles.at(i).GetMineStatus()) {
					if (!tiles.at(i).GetFlagStatus()) {
						tiles.at(i).SetFlag();
					}
				}
			}
			counter.SetCounterZero(); 
			counter.UpdateCount(); 
			menuButtons.at(0).ChangeFace(1);
			gameOver = true;
		}
	}
}

unsigned int Board::GetXTileCount()
{
	return xtileCount;
}

unsigned int Board::GetYTileCount()
{
	return ytileCount;
}

bool Board::GetResetStatus()
{
	return resetGame; 
}

unsigned int Board::GetTestQue()
{
	if (queTest1)
		return 1;
	else if (queTest2)
		return 2;
	else if (queTest3)
		return 3;
	else
		return 0; 
}
