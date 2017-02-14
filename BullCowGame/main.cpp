/* This is the console executable, that makes use of the BullCow Class
This acts as the view in a MVC patter, and is responsible for all user
interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintGuess(FText Guess);
void PrintGameSummary();
bool AskToPlayAgain();

FBullCowGame BCGame;

int main() {
	bool bPlayAgain = false;
	do	{
		PrintIntro();
		PlayGame();		
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	return 0; // exit the application
}

// Introduce the game
void PrintIntro() {
	std::cout << "Welcome to Bulls and Cows, a fun word game\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinkg of?\n";
	std::cout << std::endl;
	return;
}

// Play Game
void PlayGame() {
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	
	// loop asking for guesses while the game is not won and there are still guesses remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {				
		FText Guess = GetValidGuess();

		// Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << std::endl;
		PrintGuess(Guess);		
	}

	PrintGameSummary();
	
	// TODO add a game summary
	return;
}

// Get a valid guess from the player
FText GetValidGuess() {
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";

	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << ". Please enter your guess: ";
		
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters. \n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters. \n";
			break;
		default:			
			break; // Assume the guess is valid
		}

		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); // Keep looping until we get a valid guess

	return Guess;
}

// Print the guess back to the player
void PrintGuess(FText Guess) {
	std::cout << "Your guess was: " << Guess << std::endl;
	return;
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "Congrats you guessed the word!\n";
	}
	else {
		std::cout << "Sorry please play again.\n";
	}

	return;
}

bool AskToPlayAgain() {
	std::cout << "Would you like to play again? (Y/N) ";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'Y' || Response[0] == 'y');
}

