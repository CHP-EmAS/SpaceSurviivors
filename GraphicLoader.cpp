#include "GraphicLoader.h"

const sf::Texture& GraphicLoader::getTexture(GraphicService::Texture texture) const
{
	switch(texture)
	{
	case Player:
		return text_Player;
		break;
	case Bullets:
		return text_Bullets;
		break;
	case Asteroid:
		return text_Asteroid;
		break;
	case Background_0:
		return text_Background_0;
		break;
	case Background_1:
		return text_Background_1;
		break;
	case Background_2:
		return text_Background_2;
		break;
	case Background_3:
		return text_Background_3;
		break;
		break;
	default:
		return text_Player;
		break;
	}
}

const sf::Font& GraphicLoader::getFont(GraphicService::Font font) const
{
	switch(font)
	{
	case Arial:
		return arial_Font;
		break;
	case Pixel:
		return pixel_Font;
		break;
	default:
		return arial_Font;
		break;
	}
}

void GraphicLoader::loadAllGraphics()
{
    sf::Image img;

	if (!img.loadFromFile("img/bullets.png")) {
		loadingFails++;
	} else {
		text_Bullets.loadFromImage(img);
	}

	if (!img.loadFromFile("img/player.png")) {
		loadingFails++;
	} else {
		text_Player.loadFromImage(img);
	}

	if (!img.loadFromFile("img/asteroid.png")) {
		loadingFails++;
	} else {
		text_Asteroid.loadFromImage(img);
	}

	if (!img.loadFromFile("img/bg0.png")) {
		loadingFails++;
	}
	else {
		text_Background_0.loadFromImage(img);
	}

	if (!img.loadFromFile("img/bg1.png")) {
		loadingFails++;
	}
	else {
		text_Background_1.loadFromImage(img);
	}

	if (!img.loadFromFile("img/bg2.png")) {
		loadingFails++;
	}
	else {
		text_Background_2.loadFromImage(img);
	}

	if (!img.loadFromFile("img/bg3.png")) {
		loadingFails++;
	}
	else {
		text_Background_3.loadFromImage(img);
	}
}

void GraphicLoader::loadAllFonts()
{
	if (!arial_Font.loadFromFile("fonts\\arial.ttf")) {
		loadingFails++;
	}

	if (!pixel_Font.loadFromFile("fonts\\pixel.otf"))
	{
		loadingFails++;
	}
}

bool GraphicLoader::loadingSuccessful()
{
	return (loadingFails <= 0);
}
