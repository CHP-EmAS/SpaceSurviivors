#include "EmbeddedGraphicLoader.h"

#include "PlayerImage.h"
#include "BulletsImage.h"
#include "AsteroidImage.h"
#include "ExplosionImage.h"

#include "BackgroundImage0.h"
#include "BackgroundImage1.h"
#include "BackgroundImage2.h"
#include "BackgroundImage3.h"

#include "UiFrameImage.h"
#include "UiBlueBarImage.h"
#include "UiRedBarImage.h"

#include "ArialFont.h"
#include "PixelFont.h"

const sf::Texture& EmbeddedGraphicLoader::getTexture(GraphicService::Texture texture) const
{
	switch (texture)
	{
	case Player:
		return text_Player;
	case Asteroid:
		return text_Asteroid;
	case Bullets:
		return text_Bullets;
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
	default:
		return text_Player;
	}
}

const sf::Font& EmbeddedGraphicLoader::getFont(GraphicService::Font font) const
{
	switch (font)
	{
	case Arial:
		return arial_font;
	case Pixel:
		return pixel_font;
	default:
		return arial_font;
	}
}

EmbeddedGraphicLoader::EmbeddedGraphicLoader()
{
	text_Player.loadFromMemory(emb_player_img, sizeof(emb_player_img));
	text_Asteroid.loadFromMemory(emb_asteroid_img, sizeof(emb_asteroid_img));
	text_Bullets.loadFromMemory(emb_bullets_img, sizeof(emb_bullets_img));
	
	text_Background0.loadFromMemory(emb_bg0_img, sizeof(emb_bg0_img));
	text_Background1.loadFromMemory(emb_bg1_img, sizeof(emb_bg1_img));
	text_Background2.loadFromMemory(emb_bg2_img, sizeof(emb_bg2_img));
	text_Background3.loadFromMemory(emb_bg3_img, sizeof(emb_bg3_img));
	
	text_ui_frame.loadFromMemory(emb_frame_img, sizeof(emb_frame_img));
	text_ui_blueBar.loadFromMemory(emb_blueBar_img, sizeof(emb_blueBar_img));
	text_ui_redBar.loadFromMemory(emb_redBar_img, sizeof(emb_redBar_img));

	sf::Image explosionImg;
	explosionImg.loadFromMemory(emb_explosion_img, sizeof(emb_explosion_img));
	explosionImg.createMaskFromColor(sf::Color(255, 192, 255));
	text_ExplosionAnimation.loadFromImage(explosionImg);

	arial_font.loadFromMemory(emb_arial_font, sizeof(emb_arial_font));
	pixel_font.loadFromMemory(emb_pixel_font, sizeof(emb_pixel_font));
}
