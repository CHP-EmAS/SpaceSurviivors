#include "ScoreBoard.h"

#include "Locator.h"

ScoreBoard::ScoreBoard()
{
	frame.setSize(sf::Vector2f(325, 150));
	frame.setOrigin(frame.getSize() / 2.f);
	frame.setScale(1.5, 1.5);
	frame.setColor(sf::Color(255, 200, 0));

	scoresText.setFont(Locator::getGraphicService().getFont(GraphicService::Pixel));
	scoresText.setFontSize(24);
	scoresText.setPosition(0, - 40);

	headlineText.setFont(Locator::getGraphicService().getFont(GraphicService::Pixel));
	headlineText.setShadowOffset(3);
	headlineText.setColor(sf::Color(255, 200, 0));
	headlineText.setFontSize(32);
	headlineText.setString("TOP 3");
	headlineText.setOrigin(headlineText.getLocalBounds().width / 2, 0);
	headlineText.setPosition(0, -100);

	queryHighscoresText();
}

void ScoreBoard::refresh()
{
	queryHighscoresText();
}

std::string ScoreBoard::convertToEntryText(std::string name, int score)
{
	name += ":";

	int nameLength = name.length();
	for (int i = 0; i < (15 - nameLength); i++) {
		name = name + " ";
	}

	std::string scoreString = std::to_string(score);

	int scoreLength = scoreString.length();
	for (int i = 0; i < (8 - scoreLength); i++) {
		scoreString = "0" + scoreString;
	}

	name += scoreString;

	return name;
}

void ScoreBoard::queryHighscoresText()
{
	std::vector<HighscoreService::Entry> list = Locator::getHighscoreService().getTopEntries(3);

	std::string strList = "";

	int listSize = std::min(3, (int)list.size());
	for (int i = 0; i < listSize; i++) {
		strList += convertToEntryText(list[i].name, list[i].score);
		strList += "\n\n";
	}

	scoresText.setString(strList);
	scoresText.setOrigin(scoresText.getLocalBounds().width / 2, 0);
}

void ScoreBoard::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(frame, states);
	target.draw(headlineText, states);
	target.draw(scoresText, states);
}
