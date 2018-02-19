// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "BlackCyborgGameMode.h"
#include "BlackCyborgHUD.h"
#include "Player/BlackCyborgPlayer.h"
#include "UObject/ConstructorHelpers.h"

ABlackCyborgGameMode::ABlackCyborgGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
//	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Characters/Main_Character/Behaviour/BP_Main_Character"));
//	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
//	HUDClass = ABlackCyborgHUD::StaticClass();
}
