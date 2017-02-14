#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() {	
	Reset();
}

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameWon; }

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
	if (!IsIsogram(Guess)) { // Not Isogram
		return EGuessStatus::Not_Isogram;
	}
	else if(!IsLowercase(Guess)){ // Not Lowercase
		return EGuessStatus::Not_Lowercase;
	} else if (GetHiddenWordLength() != Guess.length()) { // Wrong Length
		return EGuessStatus::Wrong_Length;
	}
	return EGuessStatus::OK;
}

void FBullCowGame::Reset() {
	constexpr int32 MAX_TRIES = 3;
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

bool FBullCowGame::IsIsogram(FString Word) const {

	// Treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;
	
	for (auto Letter : Word) { // Foreach letter of the word
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) { return false;	}
		LetterSeen[Letter] = true;
	}

	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const {
	// Treat 0 and 1 letter words as isograms
	if (Word.length() < 1) { return true; }

	for (auto Letter : Word) { // Foreach letter of the word		
		if (!islower(Letter)) { return false; }		
	}

	return true;
}
