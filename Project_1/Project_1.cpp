#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissor = 3 }; 
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 }; 

struct stRoundInfo
{ 
   short RoundNumber = 0; 
   enGameChoice Player1Choice; 
   enGameChoice ComputerChoice; 
   enWinner Winner; 
   string WinnerName; 
}; 

struct stGameResults
{ 
   short GameRounds = 0; 
   short Player1WinTimes = 0; 
   short Computer2WinTimes = 0; 
   short DrawTimes = 0; 
   enWinner GameWinner; 
   string WinnerName = ""; 
};

int RandomNumber(int From, int To) 
{ 
   int randNum = rand() % (To - From + 1) + From; 
   return randNum; 
} 

short ReadHowManyRounds()
{
   short GameRounds = 1;
   do
   {
      cout << "How Many Rounds 1 to 10 ? \n";
      cin >> GameRounds;
   } while (GameRounds < 0 || GameRounds > 10);
   
   return GameRounds;
}

enGameChoice ReadPlayerChoice()
{
   short Choice = 1;
   do
   {
      cout << "Your Choice: [1]:Stone, [2]:Paper, [3]:Scissors ?";
      cin >> Choice;
   } while (Choice < 1 || Choice > 3);

   return (enGameChoice) Choice;
}

enGameChoice GetComputerChoice()
{
   return (enGameChoice) RandomNumber(1, 3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
   if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
   {
      return enWinner::Draw;
   }

   switch (RoundInfo.Player1Choice)
   {
   case enGameChoice::Stone:
      if (RoundInfo.ComputerChoice == enGameChoice::Paper)
      {
         return enWinner::Computer; 
      }
      break;

   case enGameChoice::Paper:
      if (RoundInfo.ComputerChoice == enGameChoice::Scissor)
      {
         return enWinner::Computer; 
      }
      break; // Add break here

   case enGameChoice::Scissor:
      if (RoundInfo.ComputerChoice == enGameChoice::Stone)
      {
         return enWinner::Computer; 
      }
      break;
   }

   return enWinner::Player1;
}


enWinner WhoWonTheGame(short Player1WinTimes, short ComputerChoice)
{
   if (Player1WinTimes > ComputerChoice)
      return enWinner::Player1;
   else if (ComputerChoice > Player1WinTimes)
      return enWinner::Computer;
   else
      return enWinner::Draw;
}

string WinnerName(enWinner Winner)
{
   string arrWinnerName[3] = {"Player1", "Computer", "No Winner"};
   return arrWinnerName[Winner - 1];
}

string ChoiceName(enGameChoice Choice) 
{ 
   string arrGameChoices[3] = { "Stone","Paper","Scissors" }; 
   return arrGameChoices[Choice - 1]; 
} 

void SetWinnerScreenColor(enWinner Winner)
{
   switch (Winner)
   {
   case enWinner::Player1:
      system("color 2F"); // Turn the screen to Green
      break;
   case enWinner::Computer:
      system("color 4F"); // Turn the screen to Red
      cout << "\a"; // Turn Bell
   default:
      system("color 6F"); // Turn the screen to Yellow
      break;
   }
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
    cout << "-----------Round [" << RoundInfo.RoundNumber << "] -----------\n\n";
    cout << "Player1 Choice: " << ChoiceName(RoundInfo.Player1Choice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner   : [" << RoundInfo.WinnerName << "] \n";
    cout << "-------------------------------\n" << endl;
    SetWinnerScreenColor(RoundInfo.Winner);
}

stGameResults FillGameResults(int GameRounds, short Player1WinTimes, short Computer2WinTimes, short DrawTimes)
{
   stGameResults GameResults;

   GameResults.GameRounds = GameRounds;
   GameResults.Player1WinTimes = Player1WinTimes;
   GameResults.Computer2WinTimes = Computer2WinTimes;
   GameResults.DrawTimes = DrawTimes;
   GameResults.GameWinner = WhoWonTheGame(Player1WinTimes, Computer2WinTimes);
   GameResults.WinnerName = WinnerName(GameResults.GameWinner);

   return GameResults;
}

stGameResults PlayGame(short HowManyRounds)
{
   stRoundInfo RoundInfo;
   short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

   for (short GameRounds = 1; GameRounds <= HowManyRounds; GameRounds++)
   {
       cout << "\nRound [" << GameRounds << "] begins:\n";
       RoundInfo.RoundNumber = GameRounds; 
       RoundInfo.Player1Choice = ReadPlayerChoice();
       RoundInfo.ComputerChoice = GetComputerChoice();
       RoundInfo.Winner = WhoWonTheRound(RoundInfo);
       RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

       if (RoundInfo.Winner == enWinner::Player1)
           Player1WinTimes++;
       else if (RoundInfo.Winner == enWinner::Computer)
           ComputerWinTimes++;
       else
           DrawTimes++;
      
      PrintRoundResults(RoundInfo);
   }

   return FillGameResults(HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes);
}

string Tabs(short NumberOfTabs) 
{ 
     string t = ""; 
     for (int i = 1; i <= NumberOfTabs; i++) 
     { 
       t = t + "\t"; 
       cout << t; 
     } 

    return t; 
}

void ShowGameOverScreen()
{
   cout << Tabs(2) << "---------------------------------------------------\n\n";
   cout << Tabs(2) << "                +++ Game Over +++ \n";
   cout << Tabs(2) << "---------------------------------------------------\n\n";
}

void ShowFinalResults(stGameResults GameResults)
{
    cout << Tabs(2) << "------------[Game Results]------------\n\n";
    cout << Tabs(2) << "Game Rounds             : " << GameResults.GameRounds << endl;
    cout << Tabs(2) << "Player1 won times       : " << GameResults.Player1WinTimes << endl;
    cout << Tabs(2) << "Computer won times      : " << GameResults.Computer2WinTimes << endl;
    cout << Tabs(2) << "Draw Times              : " << GameResults.DrawTimes << endl;
    cout << Tabs(2) << "Final Winner            : " << GameResults.GameWinner << endl;
    cout << Tabs(2) << "------------------------------------------\n";
    SetWinnerScreenColor(GameResults.GameWinner);
}

void ResetScreen()
{
   system("cls"); 
   system("color 0F");
}

void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
      ResetScreen();
      stGameResults stGameResults = PlayGame(ReadHowManyRounds());
      ShowGameOverScreen();
      ShowFinalResults(stGameResults);
      cout << "Do you want to play again? Y/N? ";
      cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
    
}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();

    return 0;
}