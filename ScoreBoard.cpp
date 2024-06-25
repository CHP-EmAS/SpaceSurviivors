#include "ScoreBoard.h"

#include "Locator.h"

ScoreBoard::ScoreBoard()
{
	highscoreFrame.setSize(sf::Vector2f(325, 150));
	highscoreFrame.setOrigin(highscoreFrame.getSize() / 2.f);
	highscoreFrame.setScale(1.5, 1.5);
	highscoreFrame.setPosition(500, 500);
	highscoreFrame.setColor(sf::Color(255, 200, 0));

	highscoreText.setFont(Locator::getGraphicService().getFont(GraphicService::Pixel));
	highscoreText.setFontSize(24);
	highscoreText.setPosition(WINDOW_SIZE / 2, 460);
}

void ScoreBoard::refresh()
{

}
