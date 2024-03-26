#include "MenuButtons.h"

MenuButtons::MenuButtons()
{
	face.setTexture(TextureManager::GetTexture("face_happy"));
	test1.setTexture(TextureManager::GetTexture("test_1"));
	test2.setTexture(TextureManager::GetTexture("test_2"));
	test3.setTexture(TextureManager::GetTexture("test_3"));
	debug.setTexture(TextureManager::GetTexture("debug"));
}

void MenuButtons::AdjustPos(int multi, int xtileCount, int ytileCount )
{
		face.setPosition((face.getLocalBounds().width / 2) * (xtileCount / 3) + (multi * face.getLocalBounds().width), face.getLocalBounds().height * ytileCount / 2);
		test1.setPosition((face.getLocalBounds().width / 2) * (xtileCount / 3) + (multi * face.getLocalBounds().width), face.getLocalBounds().height * ytileCount / 2);
		test2.setPosition((face.getLocalBounds().width / 2) * (xtileCount / 3) + (multi * face.getLocalBounds().width), face.getLocalBounds().height * ytileCount / 2);
		test3.setPosition((face.getLocalBounds().width / 2) * (xtileCount / 3) + (multi * face.getLocalBounds().width), face.getLocalBounds().height * ytileCount / 2);
		debug.setPosition((face.getLocalBounds().width / 2) * (xtileCount / 3) + (multi * face.getLocalBounds().width), face.getLocalBounds().height * ytileCount / 2);
}

void MenuButtons::DrawButtons(sf::RenderWindow& window, int index)
{
	if(index == 0)
		window.draw(face); 
	else if(index == 1)
		window.draw(test1); 
	else if (index == 2)
		window.draw(test2); 
	else if (index == 3)
		window.draw(test3); 
	else if (index == 4)
		window.draw(debug); 
}

void MenuButtons::ChangeFace(int faceType)
{
	if (faceType == 0)
		face.setTexture(TextureManager::GetTexture("face_lose"));
	else if (faceType == 1)
		face.setTexture(TextureManager::GetTexture("face_win")); 
}

sf::FloatRect MenuButtons::ReturnPosition(int index)
{
	if (index == 0)
		return face.getGlobalBounds();
	else if (index == 1)
		return test1.getGlobalBounds(); 
	else if (index == 2)
		return test2.getGlobalBounds();
	else if (index == 3)
		return test3.getGlobalBounds();
	else if (index == 4)
		return debug.getGlobalBounds();
}


void MenuButtons::Clicked(int index)
{

}
