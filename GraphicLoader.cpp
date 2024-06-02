#include "GraphicLoader.h"

const sf::Texture& GraphicLoader::getTexture(GraphicService::Texture texture) const
{
	switch(texture)
	{
	case Player:
		return text_Player;
	case Bullets:
		return text_Bullets;
	case Asteroid:
		return text_Asteroid;
	case ExplosionAnimation:
		return text_ExplosionAnimation;
	case Background_0:
		return text_Background0;
	case Background_1:
		return text_Background1;
	case Background_2:
		return text_Background2;
	case Background_3:
		return text_Background3;
	case UI_Frame:
		return text_ui_frame;;
	case UI_BlueBar:
		return text_ui_blueBar;
	case UI_RedBar:
		return text_ui_redBar;
	case UI_YellowBar:
		return text_ui_yellowBar;
	default:
		return text_Player;
	}
}

const sf::Font& GraphicLoader::getFont(GraphicService::Font font) const
{
	switch(font)
	{
	case Arial:
		return arial_Font;
	case Pixel:
		return pixel_Font;
	default:
		return arial_Font;
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

	if (!img.loadFromFile("img/explosion.png")) {
		loadingFails++;
	} else {
		img.createMaskFromColor(sf::Color(255, 192, 255));
		text_ExplosionAnimation.loadFromImage(img);
	}

	if (!img.loadFromFile("img/bg0.png")) {
		loadingFails++;
	} else {
		text_Background0.loadFromImage(img);
	}

	if (!img.loadFromFile("img/bg1.png")) {
		loadingFails++;
	} else {
		text_Background1.loadFromImage(img);
	}

	if (!img.loadFromFile("img/bg2.png")) {
		loadingFails++;
	} else {
		text_Background2.loadFromImage(img);
	}

	if (!img.loadFromFile("img/bg3.png")) {
		loadingFails++;
	} else {
		text_Background3.loadFromImage(img);
	}

	if (!img.loadFromFile("img/ui/frame.png")) {
		loadingFails++;
	}
	else {
		text_ui_frame.loadFromImage(img);
	}

	if (!img.loadFromFile("img/ui/blueBar.png")) {
		loadingFails++;
	} else {
		text_ui_blueBar.loadFromImage(img);
	}

	if (!img.loadFromFile("img/ui/yellowBar.png")) {
		loadingFails++;
	}
	else {
		text_ui_yellowBar.loadFromImage(img);
	}

	if (!img.loadFromFile("img/ui/redBar.png")) {
		loadingFails++;
	}
	else {
		text_ui_redBar.loadFromImage(img);
	}

}

void GraphicLoader::loadAllFonts()
{
	if (!arial_Font.loadFromFile("fonts/arial.ttf")) {
		loadingFails++;
	}

	if (!pixel_Font.loadFromFile("fonts/pixel.otf"))
	{
		loadingFails++;
	}
}

bool GraphicLoader::loadingSuccessful()
{
	return (loadingFails <= 0);
}
