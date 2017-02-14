#include "FBullCowGame.h"

using int32 = int;

FBullCowGame::FBullCowGame() {	
	Reset();
}

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameWon; }

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
	if (false) { // Not Isogram
		return EGuessStatus::Not_Isogram;
	}
	else if(false){ // Not Lowercase
		return EGuessStatus::Not_Lowercase;
	} else if (GetHiddenWordLength() != Guess.length()) { // Wrong Length
		return EGuessStatus::Wrong_Length;
	}
	return EGuessStatus::OK;
}

void FBullCowGame::Reset() {
	constexpr int32 MAX_TRIES = 8;
	MyMaxTries = MAX_TRIES;
	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameWon = false;

	return;
}

// Recieves a valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
	MyCurrentTry++;
	FBullCowCount BullCowCount;
		
	int32 HiddenGuessLength = Guess.length();
	for (int32 MHWChar = 0; MHWChar < GetHiddenWordLength(); MHWChar++) {		
		for (int32 GChar = 0; GChar < HiddenGuessLength; GChar++) {		
			if (MyHiddenWord[MHWChar] == Guess[GChar]){
				if (MHWChar == GChar) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}

	if (BullCowCount.Bulls == GetHiddenWordLength()) {
		bGameWon = true;
	}

	return BullCowCount;
}
