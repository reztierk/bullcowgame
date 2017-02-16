#pragma once
#include <string>
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;

// All values initialized to 0
struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
public:	
	FBullCowGame(); // Constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;

	EGuessStatus CheckGuessValidity(FString) const;
	bool setDifficulty(int32);
	void Reset(); //TODO make a more rich return value.	
	FBullCowCount SubmitValidGuess(FString);

private:
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	int32 MyCurrentTry;
	int32 MyMaxTries;
	int32 Difficulty;
	FString MyHiddenWord;
	TMap<int32, FString> HiddenWords;
	bool bGameWon;
};