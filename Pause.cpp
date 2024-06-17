#include "Pause.h"
#include "Locator.h"

PauseScene::PauseScene() : Scene(Pause)
{
	pauseText.setString("Pause");
	pauseText.setFont(Locator::getGraphicService().getFont(GraphicService::Pixel));
	pauseText.setFontSize(55);
	pauseText.setColor(sf::Color::Yellow);
	pauseText.setOrigin(pauseText.getLocalBounds().width / 2, 0);
	pauseText.setPosition(WINDOW_SIZE / 2, 400);
	pauseText.setShadowOffset(5);

	infoText.setString("Press SPACE to continue");
	infoText.setFont(Locator::getGraphicService().getFont(GraphicService::Pixel));
	infoText.setFontSize(30);
	infoText.setOrigin(infoText.getLocalBounds().width / 2, 0);
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
