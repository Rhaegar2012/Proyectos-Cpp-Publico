#include "GameManager.h"
GameManager::GameManager(const string & textureMappingPath, const string& tileMappingPath,const string&soundFXMappingPath,  RenderSystem& renderSystem_ ,  InputSystem& inputSystem_, EntityPhysics& entityPhysics_,SoundPlayer& soundPlayer_)
	:renderSystem(renderSystem_), inputSystem(inputSystem_), physicsEngine(entityPhysics_),soundPlayer(soundPlayer_), gameWindow(sf::VideoMode({800,600}), APP_NAME), gameView(sf::FloatRect({0.f,0.f}, {800.f, 600.f}))
{
	isGameOver = true;
	resourceLoader.LoadCSVResourceMapping(textureMappingPath, TEXTURE);
	resourceLoader.LoadCSVResourceMapping(soundFXMappingPath, SOUNDFX);
	resourceLoader.LoadTileCoordinatesMapping(tileMappingPath);
	textureMapPointer = resourceLoader.GetTextureMapPointer();
	tileCoordinateMapPointer = resourceLoader.GetTileCoordinatesMapPointer();
	if (!textFont.openFromFile("Assets/Fonts/ARCADE_N.ttf"))
	{
		cout << "font didn't load correctly";
	}
	
	CreateEntities();
	
	
}

void GameManager::CreateEntities()
{
	//Environment (Tile)  Entities
	for (const auto& mapKey : *tileCoordinateMapPointer)
	{
		string tileType = mapKey.first;
		vector<map<string, int>> coordinates = mapKey.second;
		for(const auto& coordinate:coordinates)
		{
			sf::Vector2f initialPosition = { ((float)coordinate.at("x")*TEXTURE_SIZE_X) + LEVEL_ORIGIN_X,((float)coordinate.at("y")*TEXTURE_SIZE_Y) + LEVEL_ORIGIN_Y};
			Entity newTileEntity(make_unique<sf::Texture>(textureMapPointer.at(tileType)), initialPosition,&soundPlayer);
			if(tileType =="Grass"|| tileType=="Ground"||tileType=="Bridge")
			{
				newTileEntity.SetEntityType(GROUND);
			}
			else if(tileType=="Spikes")
			{
				newTileEntity.SetEntityType(SPIKE);
			}
			else if(tileType=="Platform")
			{
				newTileEntity.SetEntityType(PLATFORM);
			}
			else if(tileType=="Goal")
			{
				newTileEntity.SetEntityType(GOAL);
			}
			environmentEntities.push_back(move(newTileEntity));
			
		}
	}
	//Default textures
	sf::Texture defaultPlayerTexture = resourceLoader.GetAnimationFrame("CharacterIdle_1");
	sf::Texture defaultEnemyTexture = resourceLoader.GetAnimationFrame("EnemyMoving_1");
	sf::Texture defaultCoinTexture	= resourceLoader.GetAnimationFrame("Coin_1");

	//Fonts
	//TODO

	//Player Entity
	player= new PlayerEntity(make_unique<sf::Texture>(defaultPlayerTexture),INITIAL_PLAYER_POSITION,&soundPlayer);
	player->SetObserver(&*this);
	gameView.setCenter(INITIAL_PLAYER_POSITION);
	gameWindow.setView(gameView);

	//Enemy Entities;
	//TODO Create enemy entities
	enemy_1= new EnemyEntity(make_unique<sf::Texture>(defaultEnemyTexture), INITIAL_ENEMY_POSITION_1,&soundPlayer);
	enemy_1->SetPatrolPosition(FINAL_PATROL_POSITION_ENEMY_1);
	enemy_1->SetObserver(&*this);

	enemy_2 = new EnemyEntity(make_unique<sf::Texture>(defaultEnemyTexture), INITIAL_ENEMY_POSITION_2,&soundPlayer);
	enemy_2->SetPatrolPosition(FINAL_PATROL_POSITION_ENEMY_2);
	enemy_2->SetObserver(&*this);


	enemy_3 = new EnemyEntity(make_unique<sf::Texture>(defaultEnemyTexture), INITIAL_ENEMY_POSITION_3,&soundPlayer);
	enemy_3->SetPatrolPosition(FINAL_PATROL_POSITION_ENEMY_3);
	enemy_3->SetObserver(&*this);
	
	enemyEntities.push_back(enemy_1);
	enemyEntities.push_back(enemy_2);
	enemyEntities.push_back(enemy_3);
	
	//Coin Entities
	coin_1 = new ItemEntity(make_unique<sf::Texture>(defaultCoinTexture), COIN_INITIAL_POSITION, &soundPlayer);
	coin_1->SetObserver(&*this);

	itemEntities.push_back(coin_1);
	
	//UI entities
	scoreTextLabel		 = make_unique<UILabel>(POINT_LABEL_TEXT, CHARACTER_SIZE,textFont, SCORE_TEXT_INITIAL_POSITION);
	playerLivesTextLabel = make_unique<UILabel>(LIVE_LABEL_TEXT, CHARACTER_SIZE,textFont, LIVES_TEXT_INITIAL_POSITION);
	UILabels.push_back(move(scoreTextLabel));
	UILabels.push_back(move(playerLivesTextLabel));


}

void GameManager::RunGame()
{
	sf::Clock clock;
	while (gameWindow.isOpen())
	{
		
		while (const std::optional event = gameWindow.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				gameWindow.close();
			}
		}

		float deltaTime = clock.restart().asSeconds();
		
		if(!player->IsDead())
		{
			//Process Input
			inputSystem.HandlePlayerInput(*player, deltaTime);
			//Update Game State
			
		}
		UpdateGameState(deltaTime);
		//Render
		renderSystem.Render(environmentEntities,enemyEntities,UILabels,itemEntities,*player,gameWindow);

	}
	
}

void GameManager::UpdateGameState(float deltaTime)
{
	
	if (player->IsDead())
	{
		return;
	}
	//Handle Player Collisions with Environment
	bool isOnGround=DetectEnvironmentCollision(*player,deltaTime);

	EntityStates currentPlayerState = player->GetCurrentState();
	
	//Verify player state during jump apply gravity after transition from jump->falling
    if (currentPlayerState == FALLING || (!isOnGround && currentPlayerState != GROUNDED)) {
		physicsEngine.ApplyGravity(*player, deltaTime);
		player->UpdateCurrentState(FALLING);
	}

	//Player updates physics for movement 
	player->UpdatePhysics(deltaTime);

	//Update player lives
	lives = player->GetNumberOfLives();

	//Apply physics to falling platforms
	for (int i = 0; i<environmentEntities.size(); i++)
	{
		if(environmentEntities[i].IsFalling())
		{
			physicsEngine.ApplyGravity(environmentEntities[i],deltaTime);	
		}
		environmentEntities[i].UpdatePhysics(deltaTime);
	}

	//Run current animation cycle
	player->RunAnimationCycle(deltaTime);
	//Center view on player
	
	if (player->GetCurrentState()!=FALLING)
	{
		gameView.setCenter(player->GetPosition());
		
	}
	gameWindow.setView(gameView);

	//Process enemy entities movement
	for (int i = 0; i<enemyEntities.size(); i++)
	{
	
		if(!enemyEntities[i]->IsDead())
		{
			enemyEntities[i]->Patrol(deltaTime);
			enemyEntities[i]->UpdatePhysics(deltaTime);
		}
		enemyEntities[i]->RunAnimationCycle(deltaTime);
	}

	//Run items animation cycle
	for(int i=0;i<itemEntities.size();i++)
	{
		if(itemEntities[i]->IsActive())
		{
			itemEntities[i]->UpdatePhysics(deltaTime);
			itemEntities[i]->RunAnimationCycle(deltaTime);
		}
	}

	//Updates UI State
	UpdateUIState(deltaTime);

}

bool GameManager:: DetectEnvironmentCollision(PlayerEntity& colliderEntity,float deltaTime)
{
	bool hasCollision = false;
	//Environment Collision
	for(int i=0;i<environmentEntities.size();i++)
	{
		if(player->OnCollisionEntry(environmentEntities[i],deltaTime))
		{
			hasCollision = true;
			break;
		}
	}

	//Enemy Collision
	for(int i=0;i<enemyEntities.size();i++)
	{
		if(player->OnCollisionEntry(*enemyEntities[i],deltaTime) && enemyEntities[i]->GetCurrentState()!=DEAD)
		{
			hasCollision = true;
			break;
		}
	}

	//Item Collision
	for(int i=0;i<itemEntities.size();i++)
	{
		if(player->OnCollisionEntry(*itemEntities[i],deltaTime))
		{
			hasCollision = true;
		}

	}

	//Only set falling if we're not on ground and not already jumping

	if(!hasCollision && player->GetCurrentState()!=JUMPING)
	{
		player->DelayStateUpdate(FALLING, deltaTime);
	}
	
	return hasCollision;
}

void GameManager::UpdateUIState(float deltaTime)
{
	ostringstream updatedLivesString;
	ostringstream updatedScoreString;

	updatedLivesString << "Lives x" << lives;
	updatedScoreString << "Score x" << points;

	string updatedLives = updatedLivesString.str();
	string updatedScores = updatedScoreString.str();

	UILabels[0].get()->UpdateLabelText(updatedLives);
	UILabels[1].get()->UpdateLabelText(updatedScores);
	
}

void GameManager::UpdateGameScore(int score)
{
	points += score;
}

void GameManager::OnNotify(Entity& entity, Events event, int scoreValue)
{
	points += scoreValue;
}

