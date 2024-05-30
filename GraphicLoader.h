#pragma once
#include "GraphicService.h"
class GraphicLoader : public GraphicService
{
public:
	void loadAllGraphics();
	void loadAllFonts();

	bool loadingSuccessful();
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

	sf::Texture text_ui_shortPanel;
	sf::Texture text_ui_longPanel;
	sf::Texture text_ui_blueBar;

	//Fonts
	sf::Font arial_Font;
	sf::Font pixel_Font;

	short loadingFails;

	// Geerbt über GraphicService
	const sf::Texture& getTexture(Texture texture) const override;
	const sf::Font& getFont(Font font) const override;
};

