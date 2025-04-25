#pragma once
#ifndef GAME_H
#define GAME_H
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<iostream>
#include"PLAYER.H"
#include"AlienFleet.h";
#include"Button.h"
#include"UILabel.h"



enum GameState 
{
    TITLE_SCREEN,
    GAME_SCREEN,
    GAME_OVER_SCREEN
};
class Game
{

private: 
    //Constants
    const int   RECOVERY_TIME                     = 10;
    const int   BUTTON_CHARACTER_SIZE             = 24;
    const int   TITLE_CARD_CHARACTER_SIZE         = 42;
    const int   SCORE_CHARACTER_SIZE              = 24;
    const int   GAME_OVER_CHARACTER_SIZE          = 42;
    const int   TOTAL_SCORE_CHARACTER_SIZE        = 42;
    const float BUTTON_WIDTH                      = 280.f;
    const float BUTTON_HEIGHT                     = 60.f;
    const string START_TEXT                       = "START GAME";
    const string CLOSE_GAME_TEXT                  = "CLOSE";
    const string BACK_MENU_TEXT                   = "BACK TO MENU";
    const sf::Vector2f BUTTON_SIZE                = { BUTTON_WIDTH,BUTTON_HEIGHT };
    const sf::Vector2f START_BUTTON_POS           = {200.f,330.f};
    const sf::Vector2f CLOSE_BUTTON_POS           = { 200.f,400.f };
    const sf::Vector2f BACK_MENU_BUTTON_POS       = { 200.f,330.f };
    const sf::Vector2f TITLE_SCREEN_TEXT_POSITION = { 20.f,100.f };
    const sf::Vector2f SCORE_TEXT_POSITION        = { 10.f,30.f };
    const sf::Vector2f LIVES_TEXT_POSITION        = { 100.f,30.f };
    const sf::Vector2f GAME_OVER_TEXT_POSITION    = { 150.f,100.f };
    const sf::Vector2f TOTAL_SCORE_TEXT_POSITION  = { 250.f,150.f };
    

    
    //Game Elements
    AlienFleet& alienFleet;
    Player& player;
    sf::RenderWindow gameWindow;
    vector<Bullet*> alienBullets;
    
    //State Variables
    float reloadCounter;
    float reloadRateThreshold;
    int recoveryCounter;
    int totalScore;
    int playerLives;
    bool isGameOver;
    string titleCardText = "SPACE INVADERS";
    string scoreText = "0000";
    string totalScoreText = "0000";
    string livesCounterText = "LIVES X 3";
    string gameOverText = "GAME OVER";
    GameState state;
    
    //Textures and Sprites
    vector<sf::Sprite> playerSpriteContainer;
    vector<sf::Sprite> alienSpriteContainer;
    sf::Texture playerTexture;
    vector<sf::Texture> alienTextureContainer;
    
    //Game UI Elements
    sf::Font labelFont;
    unique_ptr<Button> startGameButtonPtr;
    unique_ptr<Button> closeGameButtonPtr;
    unique_ptr<Button> backToMenuButtonPtr;
    unique_ptr<UILabel> mainTitleTextPtr;
    unique_ptr<UILabel> scoreTextPtr;
    unique_ptr<UILabel> totalScoreTextPtr;
    unique_ptr<UILabel> livesCounterTextPtr;
    unique_ptr<UILabel> gameOverMessageTextPtr;




public:
    Game(AlienFleet &alienFleet,Player &playerCannon);
    void Run();
private:

    void Update();
    void Render();
    void CreateSprites();
    void DrawFrame(sf::RenderWindow& gameWindow);
    void GameFrame(sf::RenderWindow& gameWindow);
    void GameOverFrame(sf::RenderWindow& gameWindow);
    void TitleScreenFrame(sf::RenderWindow& gameWindow);
    void HandlePlayerInput(float deltaTime);
    void HandleGameObjectsMovement(float deltaTime);
    void HandleGameObjectsCollisions();
    void HandleAlienFleetAttack();
    void UpdateGameState(float deltaTime);
    void UpdatePlayerScore(int score);
    bool IsGameOver();
    
  
};
#endif
