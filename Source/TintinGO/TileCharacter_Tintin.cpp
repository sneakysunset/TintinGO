#include "TileCharacter_Tintin.h"

ATileCharacter_Tintin* ATileCharacter_Tintin::SingletonInstance = nullptr;

ATileCharacter_Tintin* ATileCharacter_Tintin::GetInstance() 
{
	return SingletonInstance;
}