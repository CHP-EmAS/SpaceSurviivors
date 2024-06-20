#pragma once
#include "GraphicService.h"

class EmbeddedGraphicLoader : public GraphicService
{
public:
	EmbeddedGraphicLoader();

private:
	//Textures
	sf::Texture text_Player;
	sf::Texture text_Asteroid;
	sf::Texture text_Bullets;

	sf::Texture text_ExplosionAnimation;

	sf::Texture text_Background0;
	sf::Texture text_Background1;
	sf::Texture text_Background2;
	sf::Texture text_Background3;

	sf::Texture text_ui_frame;
	sf::Texture text_ui_blueBar;
	sf::Texture text_ui_redBar;

	//Fonts
	sf::Font arial_font;
	sf::Font pixel_font;

	const sf::Texture& getTexture(Texture texture) const override;
	const sf::Font& getFont(Font font) const override;
};