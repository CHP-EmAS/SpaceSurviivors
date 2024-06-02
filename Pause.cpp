#include "Pause.h"
#include "Locator.h"

PauseScene::PauseScene() : Scene(Pause)
{
	sf::Text text = sf::Text("Pause", Locator::getGraphicService().getFont(GraphicService::Pixel), 55);
	text.setLineSpacing(2);
	text.setFillColor(sf::Color::Yellow);
	pauseText.setText(text);
	pauseText.setOrigin(text.getLocalBounds().width / 2, 0);
	pauseText.setPosition(WINDOW_SIZE / 2, 400);
	pauseText.setShadowOffset(5);

	text = sf::Text("Press SPACE to continue", Locator::getGraphicService().getFont(GraphicService::Pixel), 30);
	infoText.setText(text);
	infoText.setOrigin(text.getLocalBounds().width / 2, 0);
	infoText.setPosition(WINDOW_SIZE / 2, 500);
	infoText.setShadowOffset(3);
}

void PauseScene::updateScene(sf::Time deltaTime)
{
}

void PauseScene::drawScene(sf::RenderWindow& mainWindow)
{
	Locator::getSceneManager().getLastScene()->drawScene(mainWindow);

	mainWindow.draw(pauseText);
	mainWindow.draw(infoText);
}

void PauseScene::checkEvents(sf::Event newEvent)
{
	switch (newEvent.type)
	{
	case sf::Event::KeyPressed:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			Locator::getSceneManager().changeScene(Scene::Game);
		}
		break;
	}
}

void PauseScene::loadScene()
{
}

void PauseScene::restartScene()
{
}

void PauseScene::closeScene()
{
}
