//============================================================================
// Name        : TicTacToe.cpp
// Author      : Jose
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstring>
#include <cctype>
#include <climits>
using namespace std;

//Game Functions

void PlayGame();
void GetPlayerMove();
bool CheckIfValidPosition(int position);

void GetComputerMove();
bool VerifyGameWin(char symbolToCheck);
bool VerifyCatGame();
void DrawBoard();

//MinMax Support Functions
void MakeMove(int moveIndex,char moveMark);
void UndoMove(int moveIndex);
int  EvaluateBoard();
bool TerminalState();
int  FindBestMove();
int  MiniMax(int depth,bool isComputerTurn);


//Constants
const int BOARD_SIZE 				= 9;
const  int IGNORE_CHARS				=256;
const char  PLAYER_MARK				='X';
const char  COMPUTER_MARK			='O';
const char * INPUT_ERROR_STRING		= "Wrong Input! enter a number from 0 to 9!";
const int POSSIBLE_WIN_SCENARIOS	=8;
const int REQUIRED_WIN_SYMBOLS 		=3;
//Attributes
string * endGameMessage 			= nullptr;
int  playerPosition;
char boardArray[]= {'0','1','2','3','4','5','6','7','8','9'};
bool isGameOver = false;
bool isCatGame  = false;
int  winScenarios[POSSIBLE_WIN_SCENARIOS][REQUIRED_WIN_SYMBOLS]={{0,1,2},{3,4,5},{6,7,8},
						 	 	 	 	 	 	 	 	 	 	 {0,3,6},{1,4,7},{2,4,6},
																 {6,7,8},{2,5,8}};



//Methods
void PlayGame()
{
	do
	{
		DrawBoard();
		GetPlayerMove();
		DrawBoard();
		GetComputerMove();

	}while(!isGameOver);
}

void GetPlayerMove()
{
	bool failure;
	do
	{
		cout<< "Enter position for marking, number 0 to 9"<< endl;
		cin>>playerPosition;
		if(cin.fail())
		{
			cin.clear();
			cin.ignore(IGNORE_CHARS,'\n');
			cout<<INPUT_ERROR_STRING<<endl;
			failure=true;

		}
		else
		{
			if(!CheckIfValidPosition(playerPosition))
			{
				cout << "Position already occupied, try again!";
				failure=true;
			}
			boardArray[playerPosition]=PLAYER_MARK;

		}

	}while(failure);
}

void DrawBoard()
{
	for(int i=0;i<BOARD_SIZE;i+=3)
	{
		cout<<"+----+----+----+"			 <<endl;
		cout<<"|  "<<boardArray[i]<<" |  "<<boardArray[i+1]<<" |  "<<boardArray[i+2]<<" |"<<endl;

	}
	cout<<"+----+----+----+"			 <<endl;
}


void GetComputerMove()
{
	int computerMove = FindBestMove();
	boardArray[computerMove]=COMPUTER_MARK;

}

int MiniMax(int depth, bool isComputerTurn)
{
	if(TerminalState())
	{
		return EvaluateBoard();
	}
	if(isComputerTurn)
	{
		int bestScore = INT_MIN;
		for(int i=0;i<BOARD_SIZE;i++)
		{
			if(CheckIfValidPosition(i))
			{
				MakeMove(i,COMPUTER_MARK);
				int score=MiniMax(depth+1,false);
				UndoMove(i);
				bestScore = max(bestScore,score);
			}
		}
		return bestScore;
	}
	else
	{
		int bestScore= INT_MAX;
		for(int i=0;i<BOARD_SIZE;i++)
		{
			if(CheckIfValidPosition(i))
			{
				MakeMove(i,PLAYER_MARK);
				int score = MiniMax(depth+1,true);
				UndoMove(i);
				bestScore=min(bestScore,score);
			}
		}
		return bestScore;
	}

}


int FindBestMove()
{
	int bestMove	=0;
	int bestScore   = INT_MIN;
	for (int i=0;i<BOARD_SIZE;i++)
	{

		if(CheckIfValidPosition(i))
		{
			MakeMove(i,PLAYER_MARK);
			int score = MiniMax(0,false);
			UndoMove(i);
			if (score>bestScore)
			{
				bestScore = score;
				bestMove  = i;

			}

		}
	}
	return bestMove;
}

void MakeMove(int moveIndex, char moveMark)
{
	boardArray[moveIndex]=moveMark;
}

void UndoMove(int moveIndex)
{
	boardArray[moveIndex]=(char)moveIndex;
}

int EvaluateBoard()
{
	if(VerifyGameWin(COMPUTER_MARK))
	{
		return 10;
	}

	else if (VerifyGameWin(PLAYER_MARK))
	{
		return -10;
	}
	else
	{
		return 0;
	}
}


bool TerminalState()
{
	if(VerifyGameWin(PLAYER_MARK) || VerifyGameWin(COMPUTER_MARK) || VerifyCatGame())
	{
		return true;
	}
	return false;
}


bool VerifyGameWin(char symbolToCheck)
{
	//Verify if there is a win combination
	char * combinationArray=new char[REQUIRED_WIN_SYMBOLS];

	for(int i=0;i<POSSIBLE_WIN_SCENARIOS;i++)
	{
		for(int j=0;j<REQUIRED_WIN_SYMBOLS;j++)
		{
			int  boardIndex= winScenarios[i][j];
			char boardChar = boardArray[boardIndex];
			combinationArray[j]=boardChar;
		}
		if(combinationArray[0]==symbolToCheck &&
		   combinationArray[1]==symbolToCheck &&
		   combinationArray[2]==symbolToCheck)
		{
			return true;
		}
	}
	return false;


}


bool VerifyCatGame()
{
	int numberOfOccupiedPositions=0;
	//Verify if the entire board is occupied without a win combination
	for(int i=0;i<BOARD_SIZE;i++)
	{
		char positionChar = boardArray[i];
		if (positionChar==PLAYER_MARK || positionChar==COMPUTER_MARK)
		{
			numberOfOccupiedPositions=numberOfOccupiedPositions+1;
		}
	}
	if(numberOfOccupiedPositions==BOARD_SIZE-1)
	{
		isCatGame=true;
		return true;
	}
	return false;

}




bool CheckIfValidPosition(int position)
{

	char positionValue=boardArray[position];
	if(positionValue == 'X' || positionValue =='O')
	{
		return false;
	}
	return true;
}




int main()
{
	PlayGame();
}
