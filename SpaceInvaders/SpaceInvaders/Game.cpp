#include "Game.h"
//=====================================================
//Constructor
//=====================================================
Game::Game(AlienFleet& alienFleetRef, Player& playerRef):alienFleet(alienFleetRef), player(playerRef), gameWindow(sf::VideoMode({ 640,480 }), "Space Invaders")
{
	state				= TITLE_SCREEN;
	isGameOver			= false;
	totalScore			= 0;
	reloadCounter		= 0;
	recoveryCounter		= 0;
	reloadRateThreshold	= 200;
	playerLives			= 3;

	sf::Vector2f buttonSize = { BUTTON_WIDTH,BUTTON_HEIGHT };
	if (!labelFont.openFromFile("Assets/ARCADE_N.ttf")) 
	{
		cout << "font didn't load correctly";
	}
	
	//Buttons
	startGameButtonPtr=make_unique<Button>(BUTTON_SIZE,START_BUTTON_POS, labelFont, BUTTON_CHARACTER_SIZE,START_TEXT);
	closeGameButtonPtr=make_unique<Button>(BUTTON_SIZE, CLOSE_BUTTON_POS, labelFont, BUTTON_CHARACTER_SIZE, CLOSE_GAME_TEXT);
	backToMenuButtonPtr= make_unique<Button>(BUTTON_SIZE, BACK_MENU_BUTTON_POS, labelFont, BUTTON_CHARACTER_SIZE, BACK_MENU_TEXT);
	//Labels
	mainTitleTextPtr=make_unique<UILabel>(titleCardText, TITLE_CARD_CHARACTER_SIZE, labelFont,TITLE_SCREEN_TEXT_POSITION);
	scoreTextPtr=make_unique<UILabel>(scoreText, SCORE_CHARACTER_SIZE, labelFont,SCORE_TEXT_POSITION);
	livesCounterTextPtr = make_unique<UILabel>(livesCounterText, SCORE_CHARACTER_SIZE, labelFont, LIVES_TEXT_POSITION);
	totalScoreTextPtr=make_unique<UILabel>(totalScoreText, TOTAL_SCORE_CHARACTER_SIZE, labelFont,TOTAL_SCORE_TEXT_POSITION);
	gameOverMessageTextPtr=make_unique<UILabel>(gameOverText, GAME_OVER_CHARACTER_SIZE, labelFont,GAME_OVER_TEXT_POSITION);
	
}


//=====================================================
//Behaviours
//=====================================================

void Game::Run()
{
	sf::Clock clock;
	CreateSprites();
	while (gameWindow.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();
		while (const std::optional event = gameWindow.pollEvent())
		{
			if(event->is<sf::Event::Closed>())
			{
				gameWindow.close();
			}
			if (event->is<sf::Event::MouseButtonPressed>())
			{
				// Check each button
				if (startGameButtonPtr->IsMouseOver(gameWindow) && state==TITLE_SCREEN)
				{
					cout << "Start button clicked via direct event" << endl;
					state = GAME_SCREEN;
				}
				else if (backToMenuButtonPtr->IsMouseOver(gameWindow))
				{
					state = TITLE_SCREEN;
				}
				else if (closeGameButtonPtr->IsMouseOver(gameWindow) &&(state==TITLE_SCREEN||state==GAME_OVER_SCREEN))
				{
					gameWindow.close();
				}
			}

			if(event->is<sf::Event::MouseButtonReleased>())
			{
				startGameButtonPtr->ResetButton();
				closeGameButtonPtr->ResetButton();
				backToMenuButtonPtr->ResetButton();
			}
		}
		Update();
		UpdateGameState(deltaTime);
		if(state ==GAME_SCREEN)
		{
			HandlePlayerInput(deltaTime);
			HandleGameObjectsMovement(deltaTime);
			HandleAlienFleetAttack();
			HandleGameObjectsCollisions();
		}

	}
}

void Game::Update()
{
	Render();
	
}

void Game::Render()
{

	gameWindow.clear();
	DrawFrame(gameWindow);
	gameWindow.display();

};

void Game::CreateSprites() 
{
	//Player Sprites
	playerTexture = player.GetTexture();
	sf::Sprite playerSprite(playerTexture);
	playerSpriteContainer.push_back(playerSprite);
}


void Game::DrawFrame(sf::RenderWindow& gameWindow)
{
	switch(state)
	{
		case GAME_SCREEN:
			GameFrame(gameWindow);
			break;
		case TITLE_SCREEN:
			TitleScreenFrame(gameWindow);
			break;
		case GAME_OVER_SCREEN:
			GameOverFrame(gameWindow);
			break;
		default:
			break;

	}

	
}

void Game:: GameFrame(sf::RenderWindow &gameWindow)
{
	//Player Sprites
	if (player.IsActive())
	{
		playerSpriteContainer[0].setPosition({ player.GetPosition()[0],player.GetPosition()[1] });
		player.SetSprite(make_unique<sf::Sprite>(playerSpriteContainer[0]));
		player.SetCollisionBox();
		gameWindow.draw(playerSpriteContainer[0]);

	}

	//Alien Sprites
	for (int i = 0; i < alienFleet.alienFleet.size(); i++)
	{
		Alien& alien = *alienFleet.alienFleet[i];
		sf::Sprite* alienSprite = alien.GetSprite();
		if (alienSprite && alien.IsActive())
		{
			alienSprite->setPosition({ alien.GetPosition()[0],alien.GetPosition()[1] });
			alienFleet.alienFleet[i]->SetCollisionBox();
			gameWindow.draw(*alienSprite);

		}




	}
	//Bullet Sprites
	Bullet* playerBullet = player.GetBullet();
	if (playerBullet != nullptr)
	{

		sf::Texture playerBulletTexture = playerBullet->GetTexture();
		sf::Sprite playerBulletSprite(playerBulletTexture);
		playerBullet->SetSprite(make_unique<sf::Sprite>(playerBulletSprite));
		playerBullet->SetCollisionBox();
		playerBulletSprite.setPosition({ playerBullet->GetPosition()[0],playerBullet->GetPosition()[1] });
		gameWindow.draw(playerBulletSprite);
	}
	//Alien Bullets
	for (int i = 0; i < alienFleet.alienFleet.size(); i++)
	{
		Alien& alien = *alienFleet.alienFleet[i];
		if (alien.IsActive())
		{
			Bullet* alienBullet = alien.GetBullet();
			if (alienBullet != nullptr)
			{
				sf::Texture alienBulletTexture = alienBullet->GetTexture();
				sf::Sprite  alienBulletSprite(alienBulletTexture);
				alienBullet->SetSprite(make_unique<sf::Sprite>(alienBulletSprite));
				alienBullet->SetCollisionBox();
				alienBulletSprite.setPosition({ alienBullet->GetPosition()[0],alienBullet->GetPosition()[1] });
				gameWindow.draw(alienBulletSprite);

			}
		}
	}

	//Score Text;
	string scoreText = to_string(totalScore);
	scoreTextPtr->UpdateLabelText(scoreText);
	scoreTextPtr->Draw(gameWindow);
	//Lives Text
	livesCounterTextPtr->Draw(gameWindow);

}

void Game::TitleScreenFrame(sf::RenderWindow& gameWindow) 
{
	mainTitleTextPtr->Draw(gameWindow);
	startGameButtonPtr->Draw(gameWindow);
	closeGameButtonPtr->Draw(gameWindow);
}

void Game::GameOverFrame(sf::RenderWindow& gameWindow) 
{
	gameOverMessageTextPtr->Draw(gameWindow);
	string finalScoreText = to_string(totalScore);
	totalScoreTextPtr->UpdateLabelText(finalScoreText);
	totalScoreTextPtr->Draw(gameWindow);
	backToMenuButtonPtr->Draw(gameWindow);
	closeGameButtonPtr->Draw(gameWindow);
}

void Game::HandlePlayerInput(float deltaTime) 
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		player.MovePlayer({-1.f,0.f},deltaTime);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) 
	{
		player.MovePlayer({ 1.f,0.f },deltaTime);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) 
	{
		player.FireCannon();
	}
}

void Game::HandleGameObjectsMovement(float deltaTime) 
{
	Bullet* playerBullet = player.GetBullet();
	if (playerBullet != nullptr) 
	{
		playerBullet->MoveBullet(-1,deltaTime);
	}
	//Move Alien Fleet
	alienFleet.MoveFleet(deltaTime);
	//Move Alien Bullets
	for (int i = 0; i < alienFleet.alienFleet.size(); i++) 
	{
		Alien& alien = *alienFleet.alienFleet[i];
		if (alien.IsActive()) 
		{
			Bullet* alienBullet = alien.GetBullet();
			if (alienBullet != nullptr) 
			{
				alienBullet->MoveBullet(1,deltaTime);
			}
		}
		
		
	}
}

void Game::HandleGameObjectsCollisions() 
{
	//Handles player bullet behavior if a bullet has been fired
	Bullet* playerBullet = player.GetBullet(); 
	if (playerBullet != nullptr) 
	{
		for (int i = 0; i < alienFleet.alienFleet.size(); i++)
		{
			Alien& alien = *alienFleet.alienFleet[i];
			if (!alien.IsActive()) 
			{
				continue;
			}
			sf::FloatRect alienCollider = alien.GetCollisionBox();
			if (playerBullet->CheckCollision(alienCollider, alienFleet.alienFleet[i].get()))
			{
				player.SetBulletStatus();
				alienFleet.alienFleet[i].get()->Die();
				UpdatePlayerScore(alienFleet.alienFleet[i]->GetScore());
			}

		}
	}
	//Handles alien fleet bullet behavior
	for (int i = 0; i < alienFleet.alienFleet.size(); i++) 
	{
		Bullet* alienBullet = alienFleet.alienFleet[i]->GetBullet();
		if (player.IsActive() && alienBullet) 
		{
			sf::FloatRect playerCollider = player.GetCollisionBox();
			if (alienBullet->CheckCollision(playerCollider, &player))
			{
				player.Die();
				string updatedLivesText = "LIVES X "+to_string(player.GetRemainingLives());
				livesCounterTextPtr->UpdateLabelText(updatedLivesText);
			}

		}
		
		
	}

}


void Game::HandleAlienFleetAttack() 
{
	if (alienFleet.CanShoot()) 
	{
		alienFleet.SelectAlienToAttack();
		alienFleet.SetShootStatus();
		reloadCounter = 0;
	}
}


void Game::UpdatePlayerScore(int score) 
{
	totalScore += score;
}


void Game::UpdateGameState(float deltaTime) 
{
	reloadCounter++;
	if (reloadCounter > reloadRateThreshold)
	{
		alienFleet.SetShootStatus();
	}
	if (!player.IsActive())
	{
		recoveryCounter++;
		if (recoveryCounter == RECOVERY_TIME)
		{
			player.ResetPlayer();
			recoveryCounter = 0;
		}
	}
	if (IsGameOver()) 
	{
		state = GAME_OVER_SCREEN; 
	}
}

bool Game::IsGameOver() 
{
	if (player.GetRemainingLives() == 0) 
	{
		
		return true;
	}
	return false;
}



