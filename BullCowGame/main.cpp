/* 
This is the console executable, that makes use of the BullCow Class
This acts as the view in a MVC patter, and is responsible for all user
interaction. For game logic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// Make syntax Unreal Friendly
using FText = std::string;
using int32 = int;

// Function prototypes as outside a class
void PrintIntro();
void PlayGame();
void ChooseDifficulty();
FText GetValidGuess();
void PrintGuess(FText Guess);
void PrintGameSummary();
bool AskToPlayAgain();

// Game class for reuse
FBullCowGame BCGame;

// Entry point fo the application
int main() {
	bool bPlayAgain = false;
	PrintIntro();
	do	{		
		PlayGame();		
		bPlayAgain = AskToPlayAgain();
		std::cout << std::endl;
	} while (bPlayAgain);

	return 0; // exit the application
}

// Introduce the game
void PrintIntro() {
	std::cout << "\n\n   Welcome to Bulls and Cows, a fun word game.\n\n";
	std::cout << "                                        /;    ;\\\n";
	std::cout << "                                    __  \\\\____//\n";
	std::cout << "                                   /{_\\_/   `'\\____\n";
	std::cout << "                                   \\___   (o)  (o  }\n";
	std::cout << "        _____________________________/          :--'\n";
	std::cout << "    ,-,'`@@@@@@@@       @@@@@@         \\_    `__\\\n";
	std::cout << "   ;:(  @@@@@@@@@        @@@             \\___(o'o)\n";
	std::cout << "   :: )  @@@@          @@@@@@        ,'@@(  `===='\n";
	std::cout << "   :: : @@@@@:          @@@@         `@@@:\n";
	std::cout << "   :: \\  @@@@@:       @@@@@@@)    (  '@@@'\n";
	std::cout << "   ;; /\\      /`,    @@@@@@@@@\\   :@@@@@)\n";
	std::cout << "   ::/  )    {_----------------:  :~`,~~;\n";
	std::cout << "  ;;'`; :   )                  :  / `; ;\n";
	std::cout << " ;;;; : :   ;                  :  ;  ; :\n";
	std::cout << " `'`' / :  :                   :  :  : :\n";
	std::cout << "     )_ \\__;      \"; \"         :_ ;  \\_\\       `,','\n";
	std::cout << "     :__\\  \\    * `,'*         \\  \\  :  \\   *  8`;'*  *\n";
	std::cout << "         `^'     \\ :/           `^'  `-^-'   \\v/ :  \\/ \n\n";	
	std::cout << std::endl;
	return;
}

// Play a single game till completion
void PlayGame() {
	BCGame.Reset();
	ChooseDifficulty();

	int32 MaxTries = BCGame.GetMaxTries();
	
	// loop asking for guesses while the game is not won and there are still guesses remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {				
		FText Guess = GetValidGuess();

		// Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << std::endl;
		std::cout << std::endl;
		
	}

	PrintGameSummary();
	
	return;
}

// Get a valid guess from the player
FText GetValidGuess() {
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";

	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Please enter your guess: ";
		
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters. \n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters. \n\n";
			break;
		default:			
			break; // Assume the guess is valid
		}
		
	} while (Status != EGuessStatus::OK); // Keep looping until we get a valid guess

	return Guess;
}

void ChooseDifficulty() {

	bool Success = false;

	do {
		FString Difficulty;
		std::cout << "What difficulty would you like to play (1-5)? ";
		std::getline(std::cin, Difficulty);
		Success = BCGame.setDifficulty(std::stoi(Difficulty));
	} while (!Success); // Keep looping until we get a valid difficulty level

	std::cout << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";

	return;
}

void PrintGuess(FText Guess) {
	std::cout << "Your guess was: " << Guess << std::endl;
	return;
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "Well done, You Win!\n";
	}
	else {
		std::cout << "Better luck next time!.\n";
	}

	return;
}

bool AskToPlayAgain() {
	std::cout << "Would you like to play again? (Y/N) ";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'Y' || Response[0] == 'y');
}
