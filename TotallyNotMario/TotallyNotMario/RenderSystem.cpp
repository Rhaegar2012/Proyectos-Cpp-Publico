#include "RenderSystem.h"

RenderSystem::RenderSystem()
{
	
}



sf::RenderWindow& RenderSystem::GetWindow()
{
	return gameWindow;
}


void RenderSystem::Render(vector<Entity> &levelEntities,
						  vector<EnemyEntity*> &enemyEntities,
						  vector<unique_ptr<UILabel>> &UILabels,
						  vector<ItemEntity*> itemEntities,
						  PlayerEntity & playerEntity,
						  sf::RenderWindow& gameWindow)
{
	
	gameWindow.clear(sf::Color::Black);
	RenderLevelEntities(levelEntities, gameWindow);
	RenderMobEntities(enemyEntities, gameWindow);
	RenderCharacter(playerEntity, gameWindow);
	RenderItems(itemEntities, gameWindow);
	RenderUI(UILabels, gameWindow);
	gameWindow.display();
}

void RenderSystem::RenderLevelEntities(vector<Entity> &levelEntities,sf::RenderWindow& gameWindow)
{
	for(int i=0;i<levelEntities.size();i++)
	{
		sf::Vector2f entityPosition = levelEntities[i].GetPosition();
		sf::Sprite* windowSprite = levelEntities[i].GetSprite();
		sf::RectangleShape entityCollider = levelEntities[i].GetColliderVisual();
		gameWindow.draw(*windowSprite);
		gameWindow.draw(entityCollider);
	}
}

void RenderSystem::RenderMobEntities(vector<EnemyEntity*> &enemyEntities,sf::RenderWindow &gameWindow )
{
	for(int i=0;i<enemyEntities.size();i++)
	{
		sf::Vector2f entityPosition = enemyEntities[i]->GetPosition();
		sf::Sprite* windowSprite = enemyEntities[i]->GetSprite();
		sf::RectangleShape entityCollider = enemyEntities[i]->GetColliderVisual();
		gameWindow.draw(*windowSprite);
		gameWindow.draw(entityCollider);
		
	}
}

void RenderSystem::RenderCharacter(Entity &playerEntity,sf::RenderWindow& gameWindow)
{
	sf::Sprite* characterSprite = playerEntity.GetSprite();
	sf::RectangleShape colliderVisual = playerEntity.GetColliderVisual();
	characterSprite->setPosition(playerEntity.GetPosition());
	gameWindow.draw(*characterSprite);
	gameWindow.draw(colliderVisual);
}


void RenderSystem::RenderItems(vector<ItemEntity*>& itemEntities , sf::RenderWindow& gameWindow )
{
	for(int i=0;i<itemEntities.size();i++)
	{
		sf::Sprite* itemSprite = itemEntities[i]->GetSprite();
		sf::RectangleShape colliderVisual = itemEntities[i]->GetColliderVisual();

		itemSprite->setPosition(itemEntities[i]->GetPosition());
		if(itemEntities[i]->IsActive())
		{
		   gameWindow.draw(*itemSprite);
		   gameWindow.draw(colliderVisual);
		}
		
	}
}

void RenderSystem::RenderUI(vector<unique_ptr<UILabel>>&UILabels, sf::RenderWindow& gameWindow)
{
	for(int i=0; i<UILabels.size();i++)
	{
		UILabels[i]->Draw(gameWindow);
	}
}

