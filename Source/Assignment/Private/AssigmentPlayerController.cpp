#include "AssigmentPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerCharacter.h"
#include "HUDViewModel.h"
#include "PauseMenuWidget.h"
#include "PauseMenuViewModel.h"
#include "HUDWidget.h"
#include "VMCharacterHealth.h"
#include "GameFramework/InputDeviceSubsystem.h"
#include "GameFramework/InputDeviceProperties.h"

void AAssigmentPlayerController::BeginPlay()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	PlayerCharacter = Cast<APlayerCharacter>(GetCharacter());

	if (PlayerCharacter != nullptr) {
		SetupUI();
	}
}

void AAssigmentPlayerController::SetGamePaused(bool bIsPaused)
{
	SetPause(bIsPaused);
}

void AAssigmentPlayerController::SetPauseMenuVisible(bool bIsVisible)
{
	if (PauseMenuWidget == nullptr) {
		return;
	}

	if (bIsVisible) {
		PauseMenuWidget->AddToViewport();
		SetInputMode(FInputModeGameAndUI());
	}
	else {
		PauseMenuWidget->RemoveFromParent();
		SetInputMode(FInputModeGameOnly());
	}
}

void AAssigmentPlayerController::QuitGame()
{
	ConsoleCommand("quit");
}

void AAssigmentPlayerController::SetupUI()
{
	if (CharacterHealthViewModelClass != nullptr && HudWidgetClass != nullptr) 
	{
		CharacterHealthViewModel = NewObject<UVMCharacterHealth>(this, CharacterHealthViewModelClass);
		CharacterHealthViewModel->SetModel(PlayerCharacter);

		HudWidget = CreateWidget<UHUDWidget>(GetWorld(), HudWidgetClass);

		if (HudWidget != nullptr && CharacterHealthViewModel != nullptr) 
		{
			HudWidget->SetCharacterHealthViewModel(CharacterHealthViewModel);
			HudWidget->AddToViewport();
		}
	}

	if (PauseMenuViewModelClass != nullptr && PauseMenuWidgetClass != nullptr) 
	{
		PauseMenuViewModel = NewObject<UPauseMenuViewModel>(this, PauseMenuViewModelClass);
		PauseMenuViewModel->SetModels(PlayerCharacter, this);

		PauseMenuWidget = CreateWidget<UPauseMenuWidget>(GetWorld(), PauseMenuWidgetClass);

		if (PauseMenuWidget != nullptr && PauseMenuViewModel != nullptr) 
		{
			PauseMenuWidget->SetViewModel(PauseMenuViewModel);
		}
	}
}