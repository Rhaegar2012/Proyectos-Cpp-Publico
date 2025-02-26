//============================================================================
// Name        : Battleship.cpp
// Author      : Jose
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Utils.h"
#include <iostream>
#include <random>
#include <map>
#include <string>
#include <algorithm>

//Enums
enum ShipType
{
	TYPE_AIRCRAFT_CARRIER,
	TYPE_BATTLESHIP,
	TYPE_CRUISER,
	TYPE_DESTROYER,
	TYPE_SUBMARINE,
	TYPE_NONE,
	TYPE_HIT
};

enum ShipOrientation
{
	HORIZONTAL,
	VERTICAL
};

enum BoardTileState
{
	NONE,
	SHIP,
	MISSED,
	HIT,
};

using namespace std;

//Constants
const int WIDTH = 10;
const int HEIGHT = 10;
const int FLEET_SIZE = 5;
const int MAX_HITS = 18;
const int ADJACENT_POSITIONS = 4;
const char* PLAYER_ROW_INPUT_PROMPT = "Enter row  (A-J)";
const char* PLAYER_COLUMN_INPUT_PROMPT = "Enter column  (0-9)";
const char* PLAYER_ROW_INPUT_ERROR = "Enter only letters from A through J";
const char* PLAYER_COLUMN_INPUT_ERROR = "Enter only numbers from 0 to 9";
const char* PLAYER_ORIENTATION_INPUT_PROMPT = "Enter Ship Orientation (H/V)";
const char* PLAYER_ORIENTATION_INPUT_ERROR = "Only enter H or V ";
const map<char, int> rowIndexDictionary = {
		{'A',0},
		{'B',1},
		{'C',2},
		{'D',3},
		{'E',4},
		{'F',5},
		{'G',6},
		{'H',7},
		{'I',8},
		{'J',9}
};

map<ShipType, int> shipSizeMap = { 
	{TYPE_AIRCRAFT_CARRIER,5},
	{TYPE_BATTLESHIP,4},
	{TYPE_CRUISER,3},
	{TYPE_DESTROYER,3},
	{TYPE_SUBMARINE,2},
	{TYPE_NONE,0},
	{TYPE_HIT,0}
};

map<ShipType, string> shipNames = {
	{TYPE_AIRCRAFT_CARRIER,"Aircraft Carrier"},
	{TYPE_BATTLESHIP,"Battleship"},
	{TYPE_CRUISER,"Cruiser"},
	{TYPE_DESTROYER,"Destroyer"},
	{TYPE_SUBMARINE,"Submarine"},
	{TYPE_NONE,"None"},
	{TYPE_HIT,"Hit"}
};

map<ShipType, string> shipCharacters = {
	{TYPE_AIRCRAFT_CARRIER,"A"},
	{TYPE_BATTLESHIP,"B"},
	{TYPE_CRUISER,"C"},
	{TYPE_DESTROYER,"D"},
	{TYPE_SUBMARINE,"S"},
	{TYPE_NONE," "},
	{TYPE_HIT,"X"}
};

//structs
struct OriginPosition
{
	int rowOrigin;
	int columnOrigin;
};

struct Ship
{
	ShipType shipType;
	string shipName;
	int size = 0;
	OriginPosition originPosition;
	ShipOrientation shipOrientation;
	string shipCharacter;
};

struct GuessBoardTile
{
	BoardTileState tileState;
};

struct ShipBoardTile
{
	BoardTileState tileState;
	Ship* ship;
};

struct Player
{
	Ship* ships[FLEET_SIZE];
	int score = 0;
	int hits  = 0;
	GuessBoardTile guessBoard[WIDTH][HEIGHT];
	ShipBoardTile  shipBoard[WIDTH][HEIGHT];
};


//state variables
bool isGameOver = false;
Player* computerPlayer;
Player* humanPlayer;
string displayGuessBoard[WIDTH][HEIGHT];
string displayFleetBoard[WIDTH][HEIGHT];
char playerMoveRow;
char playerMoveColumn;
string* computerPlayerLastHit=new string("");
string  lastHit;
bool isComputerHunting=true;


//Initialization Functions
void InitializeGame();
void InitializeFleets();
void InitializeBoards();
void PlaceFleetInBoard();
//Input Functions
void HandlePlayerMove();
void EvaluateGameOver();
void PlaceShipInBoard(Player* player, Ship* ship);
bool ValidateShipPosition(int xOrigin, int yOrigin, Ship* ship, Player* player);
char GetInputCharacter(const char* prompt, const char* error);
int  GetInputInt(const char* prompt, const char* error);
//Update UI Console Functions 
void DrawBoard();
string DrawTile(string content);
//AI Functions (Hunt and Target Algorithm)
void  HandleComputerMove();
string ChooseHuntMove(Player* player);
string ChooseTargetMove(Player* player, string* lastHit);
string ChooseHuntTargetMove(Player* player, string* lastHit, bool isHunting);
string SelectMoveFromAdjacents(string* possibleMoves,string* lastHit);
string* GetAdjacentPositions(string* lastHit);
string* GetUntriedPositions(Player* player);
char FindCharKey(map<char, int> valueMap, int value);
void UpdateGameState(Player* player, string* move, bool hit);



void InitializeGame()
{
	cout << "Welcome to BattleShip " << endl;
	cout << "Admiral, start by placing your fleet" << endl;
	computerPlayer = new Player;
	humanPlayer = new Player;
	InitializeFleets();
	InitializeBoards();

}

void InitializeFleets()
{
	
	ShipType shipTypeArray[] = { TYPE_AIRCRAFT_CARRIER, TYPE_BATTLESHIP, TYPE_CRUISER, TYPE_DESTROYER, TYPE_SUBMARINE };	
	//Initialize Player Fleet

	for (int i = 0; i < FLEET_SIZE; i++)
	{
		Ship* ship = new Ship;
		ShipType shipType = shipTypeArray[i];
		ship->shipType = shipType;
		ship->shipName = shipNames[shipType];
		ship->size = shipSizeMap[shipType];
		ship->shipCharacter = shipCharacters[shipType];
		humanPlayer->ships[i] = ship;
	
	};
	//Initialize Computer Fleets
	for (int i = 0; i < FLEET_SIZE; i++)
	{
		Ship* ship = new Ship;
		ShipType shipType = shipTypeArray[i];
		ship->shipType = shipType;
		ship->shipName = shipNames[shipType];
		ship->size = shipSizeMap[shipType];
		ship->shipCharacter = shipCharacters[shipType];
		computerPlayer->ships[i] = ship;
	}
}

void InitializeBoards()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			humanPlayer->shipBoard[i][j].tileState    = NONE;
			computerPlayer->shipBoard[i][j].tileState = NONE;
			humanPlayer->guessBoard[i][j].tileState   = NONE;
			computerPlayer->guessBoard[i][j].tileState= NONE;
		}
	}
}

void PlaceFleetInBoard()
{
	int rowIndex;
	int columnIndex;
	int randomOrientationIndex;

	
	default_random_engine generator(random_device{}());
	uniform_int_distribution<int> positionDistribution(0, 9);
	uniform_int_distribution<int> orientationDistribution(0, 1);
	
	//Read input from player and place ships
	for (int i=0 ; i<FLEET_SIZE;i++)
	{
		bool isValidPosition = false;
		Ship* ship = humanPlayer->ships[i];
		do
		{
			cout << "select placement for ship No " << i+1 << " Ship type "<<ship->shipName<<endl;
			char orientationInput = GetInputCharacter(PLAYER_ORIENTATION_INPUT_PROMPT, PLAYER_ORIENTATION_INPUT_ERROR);
			if (orientationInput == 'H')
			{
				ship->shipOrientation = HORIZONTAL;
			}
			else if (orientationInput == 'V')
			{
				ship->shipOrientation = VERTICAL;
			}
			char rowInput = GetInputCharacter(PLAYER_ROW_INPUT_PROMPT, PLAYER_ROW_INPUT_ERROR);
			int  columnInput = GetInputInt(PLAYER_COLUMN_INPUT_PROMPT, PLAYER_COLUMN_INPUT_ERROR);
			columnIndex = columnInput;
			if (rowIndexDictionary.find(rowInput) != rowIndexDictionary.end())
			{
				rowIndex = rowIndexDictionary.at(rowInput);

			}


			isValidPosition = ValidateShipPosition(rowIndex, columnIndex, ship, humanPlayer);

		} while (!isValidPosition);
		ship->originPosition.rowOrigin = rowIndex;
		ship->originPosition.columnOrigin = columnIndex;
		PlaceShipInBoard(humanPlayer, ship);
	


	};
	cout << "Good job Admiral , now wait while the enemy places their fleet" << endl;
	cout << "Placing Enemy fleet" << endl;
	//Place the computer ships randomly
	for (Ship* ship : computerPlayer->ships)
	{
		do
		{
			randomOrientationIndex = orientationDistribution(generator);
			if (randomOrientationIndex == 0) 
			{
				ship->shipOrientation = HORIZONTAL;
			}
			else 
			{
				ship->shipOrientation = VERTICAL;
			}
			rowIndex = positionDistribution(generator);
			columnIndex = positionDistribution(generator);

		} while (!ValidateShipPosition(rowIndex, columnIndex, ship, computerPlayer));
		cout << "Enemy ship placed" << endl;
		ship->originPosition.rowOrigin = rowIndex;
		ship->originPosition.columnOrigin = columnIndex;
		cout << rowIndex << columnIndex << endl;
		PlaceShipInBoard(computerPlayer, ship);
	};



}

void PlaceShipInBoard(Player* player, Ship* ship) 
{
	int rowIndex = ship->originPosition.rowOrigin;
	int colIndex = ship->originPosition.columnOrigin;
	int size = ship->size;
	ShipOrientation orientation = ship->shipOrientation;
	if (orientation == HORIZONTAL) 
	{
		for (int i = colIndex; i < size+colIndex; i++) 
		{
			player->shipBoard[rowIndex][i].ship = ship;
			player->shipBoard[rowIndex][i].tileState = SHIP;
		}
	}
	else if (orientation == VERTICAL) 
	{
		for (int i = rowIndex; i < size+rowIndex; i++) 
		{
			player->shipBoard[i][colIndex].ship = ship;
			player->shipBoard[i][colIndex].tileState = SHIP;
		}
	}
}

bool ValidateShipPosition(int rowIndex, int columnIndex, Ship* ship, Player* player)
{
	int targetPosition;
	int shipSize = ship->size;
	ShipOrientation orientation = ship->shipOrientation;
	ShipBoardTile targetTile;
	ShipBoardTile originTile;
	//Checks if origin tile is occupied
	originTile = player->shipBoard[rowIndex][columnIndex];
	if (originTile.tileState == SHIP) 
	{
		cout << "Position occupied! "<<"row "<<rowIndex<<"column "<<columnIndex << endl;
		return false;
	}
	if (orientation == HORIZONTAL)
	{
		targetPosition = columnIndex + shipSize;
		//Check if target position outside of board
		if (targetPosition < WIDTH)
		{
			targetTile = player->shipBoard[rowIndex][targetPosition];
		}
		else
		{
			cout << "Ship doesn't fit board" << endl;
			return false;
		}
		//Check if target position is occupied
		if (targetTile.tileState == NONE)
		{
			if (player == humanPlayer) 
			{
				cout << "Ship successfully placed!" << "row " << rowIndex << "column " << columnIndex << endl;
			}
			return true;
		}
		else
		{
			if (player == humanPlayer)
			{
				cout << "Board tile already occupied! " << "row " << rowIndex << "column " << columnIndex << " try again" << endl;
			}
			
			return false;
		}

	}
	else if (orientation == VERTICAL)
	{
		
		targetPosition = rowIndex + shipSize;
		targetTile = player->shipBoard[targetPosition][columnIndex];
		//Check if target position outside of board
		if (targetPosition < HEIGHT)
		{
			targetTile = player->shipBoard[rowIndex][targetPosition];
		}
		else
		{
			cout << "Ship doesn't fit board" << endl;
			return false;
		}
		//Check if target position is occupied 
		if (targetTile.tileState == NONE)
		{
			if (player == humanPlayer) 
			{
				cout << "Ship successfully placed!" << "row " << rowIndex << "column " << columnIndex << endl;
			}
			return true;
		}
		else
		{
			if (player == humanPlayer) 
			{
				cout << "Board tile already occupied! " << "row " << rowIndex << "column " << columnIndex << " try again" << endl;
			}
			return false;
		}
	}
	return false;
}

void DrawBoard()
{


	GuessBoardTile boardTile;
	//First populate the displayGuessBoard with the guessBoard state from the human player
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			string tile = " ";
			string shipCharacter = " ";
			boardTile = humanPlayer->guessBoard[i][j];
			BoardTileState tileState = boardTile.tileState;
			switch (tileState)
			{
			case NONE:
				tile = DrawTile(" ");
				break;
			case MISSED:
				tile = DrawTile("X");
				break;
			case SHIP:
				tile = DrawTile(" ");
				break;
			case HIT:
				tile = DrawTile("O");
				break;


			}
			displayGuessBoard[i][j] = tile;
		}

	}
	//Populate Player display fleet board
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			string tile = " ";
			BoardTileState tileState = humanPlayer->shipBoard[i][j].tileState;
			if (tileState == SHIP)
			{
				string shipCharacter = humanPlayer->shipBoard[i][j].ship->shipCharacter;
				tile = DrawTile(shipCharacter);
			}
			else if (tileState == HIT) 
			{
				tile = DrawTile("X");
			}
			else 
			{
				tile = DrawTile(" ");
			}
			displayFleetBoard[i][j] = tile;
		}

	}

	//draw GuessBoard
	cout << "GUESS BOARD" << endl;
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			cout << "+-+";
		}
		cout << endl;
		for (int j = 0; j < WIDTH; j++)
		{
			cout << "|" << displayGuessBoard[i][j] << "|";
		}
		cout << endl;
	}
	cout << "FLEET BOARD" << endl;
	//Draw Fleet Board
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH ; j++) 
		{
			cout << "+-+";
		}
		cout << endl;
		for (int j = 0; j < WIDTH; j++)
		{
			cout <<"|"<< displayFleetBoard[i][j]<<"|";
		}
		cout << endl;
	}
}

string DrawTile(string content) 
{
	string tile = content;
	return tile;
}


void HandlePlayerMove() 
{
	cout << "Input attack coordinates Admiral" << endl;
	playerMoveRow	 = GetInputCharacter(PLAYER_ROW_INPUT_PROMPT,PLAYER_ROW_INPUT_ERROR);
	playerMoveColumn = GetInputInt(PLAYER_COLUMN_INPUT_PROMPT, PLAYER_COLUMN_INPUT_ERROR);
	int rowIndex = rowIndexDictionary.at(playerMoveRow);
	int colIndex = playerMoveColumn;
	BoardTileState targetTileState = computerPlayer->shipBoard[rowIndex][colIndex].tileState;

	if (targetTileState == SHIP) 
	{
		cout << "Sonar reports a hit !" << endl;;
		humanPlayer->guessBoard[rowIndex][colIndex].tileState = HIT;
		humanPlayer->score += 1;
		computerPlayer->hits +=1;
	}
	else 
	{
		cout << "Splash in water!! no hit !" << endl;
		humanPlayer->guessBoard[rowIndex][colIndex].tileState = MISSED;
	}

}

void HandleComputerMove() 
{
	computerPlayerLastHit = &lastHit;
	if (!computerPlayerLastHit->empty())
	{
		isComputerHunting = false;
	}
	string move = ChooseHuntTargetMove(computerPlayer, computerPlayerLastHit, isComputerHunting);
	int rowIndex = rowIndexDictionary.at(move[0]);
	int colIndex = move[1]-'0';
	BoardTileState  targetTileState = humanPlayer->shipBoard[rowIndex][colIndex].tileState;
	if (targetTileState == SHIP) 
	{
		computerPlayer->guessBoard[rowIndex][colIndex].tileState = HIT;
		humanPlayer->shipBoard[rowIndex][colIndex].tileState = HIT;
		computerPlayer->score += 1;
		humanPlayer->hits += 1;
		lastHit = move;
	}
	else 
	{
		computerPlayer->guessBoard[rowIndex][colIndex].tileState = MISSED;

	}

}

string* GetUntriedPositions(Player* player) 
{
	string* untriedPositions = new string[HEIGHT*WIDTH];
	int index = 0;
	
	for (int i = 0; i < HEIGHT; i++) 
	{
		for (int j = 0; j < WIDTH; j++) 
		{
			BoardTileState tileState = player->guessBoard[i][j].tileState;
			if (tileState == NONE) 
			{
				char rowPosition = FindCharKey(rowIndexDictionary, i);
				string positionString= rowPosition + to_string(j);
				untriedPositions[index] = positionString;
				index++;
			}
		}
	}
	return untriedPositions;
	
}

string* GetAdjacentPositions(string* lastHit) 
{
	string* adjacentPositions= new string[ADJACENT_POSITIONS];
	string hit = *lastHit;
	int index = 0;
	int possibleMovements[2] =  { 1, -1 };
	const int positionX = rowIndexDictionary.at(hit[0]);
	const int positionY = hit[1]-'0';
	//Check X positions- validate target position to be inside board
	for (int i = 0; i < 2; i++) 
	{
		int targetX = positionX + possibleMovements[i];
		if (targetX < 0) 
		{
			targetX = 0;
		}
		char rowPosition = FindCharKey(rowIndexDictionary, targetX);
		
		if (targetX > 0 && targetX < WIDTH) 
		{
			string positionString = rowPosition + to_string(positionY);
			adjacentPositions[index] = positionString;
			++index;

		}
	
	}

	//Check Y Positions-validate target posiiton to be inside board
	for (int i = 0; i < 2; i++)
	{
		
		int targetY = positionY + possibleMovements[i];
		char rowPosition = FindCharKey(rowIndexDictionary, positionX);
		if (targetY>0 && targetY < HEIGHT)
		{
			string positionString = rowPosition + to_string(targetY);
			adjacentPositions[index] = positionString;
			++index;
		}
	
	}

	return adjacentPositions;

}

string SelectMoveFromAdjacents(string* possibleMoves,string* lastHit) 
{
	string bestMove = *lastHit;
	char  lastHitX = bestMove[0];
	char  lastHitY = bestMove[1];
	float distanceToLastHit = FLT_MAX;
	default_random_engine generator(random_device{}());
	uniform_int_distribution<int> moveDistribution(0, ADJACENT_POSITIONS-1);
	int randomIndex=moveDistribution(generator); 
	bestMove = possibleMoves[randomIndex];
	return bestMove;

}



string ChooseHuntMove(Player* player) 
{
	default_random_engine generator(random_device{}());
	uniform_int_distribution<int> moveDistribution(0, WIDTH*HEIGHT);
	string* possibleMoves = GetUntriedPositions(player);
	int randomIndex = moveDistribution(generator);
	string move = possibleMoves[randomIndex];
	return move;

}

string ChooseHuntTargetMove(Player* player, string* lastHit, bool isHunting) 
{
	string move = "";
	
	if (isHunting) 
	{
		move = ChooseHuntMove(player);
	}
	else 
	{
		move = ChooseTargetMove(player, lastHit);
	}
	return move;
}

string ChooseTargetMove(Player* player, string* lastHit) 
{
	string* possibleMoves = GetAdjacentPositions(lastHit);
	string move = SelectMoveFromAdjacents(possibleMoves,lastHit);
	return move;
}

void UpdateGameState(Player* player, char* move, bool hit) 
{

}


void EvaluateGameOver() 
{
	int playerHits = humanPlayer->hits;
	int computerHits = computerPlayer->hits;
	if (playerHits >= MAX_HITS || computerHits >= MAX_HITS) 
	{
		cout << "Game Over!" << endl;
		isGameOver = true;
	}
}


char FindCharKey(map<char, int> map, int value)
{
	char key;
	for (const auto& pair : map)
	{
		if (pair.second == value)
		{
			key = pair.first;
			break;
		}
	}
	return key;
}

int main()
{
	InitializeGame();
	PlaceFleetInBoard();
	DrawBoard();
	do 
	{
		HandlePlayerMove();
		DrawBoard();
		EvaluateGameOver();
		HandleComputerMove();
		EvaluateGameOver();
		DrawBoard();
	} while (!isGameOver);


}


