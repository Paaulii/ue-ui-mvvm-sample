#include "AssigmentPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerCharacter.h"
#include "PauseMenuWidget.h"
#include "VMPauseMenu.h"
#include "HUDWidget.h"
#include "VMCharacterHealth.h"
#include "VMSlotIndicator.h"

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
		
		SlotIndicatorViewModel = NewObject<UVMSlotIndicator>(this, SlotIndicatorViewModelClass);
		SlotIndicatorViewModel->SetModel(PlayerCharacter);
		
		HudWidget = CreateWidget<UHUDWidget>(GetWorld(), HudWidgetClass);

		if (HudWidget != nullptr)
		{
			if (CharacterHealthViewModel != nullptr)
			{
				HudWidget->OnSetCharacterHealthViewModel(CharacterHealthViewModel);
			}
			
			if (SlotIndicatorViewModel != nullptr)
			{
				HudWidget->OnSetSlotIndicatorViewModel(SlotIndicatorViewModel);
			}
			
			HudWidget->AddToViewport();
		}
	}

	if (PauseMenuViewModelClass != nullptr && PauseMenuWidgetClass != nullptr) 
	{
		PauseMenuViewModel = NewObject<UVMPauseMenu>(this, PauseMenuViewModelClass);
		PauseMenuViewModel->SetModels(PlayerCharacter, this);

		PauseMenuWidget = CreateWidget<UPauseMenuWidget>(GetWorld(), PauseMenuWidgetClass);

		if (PauseMenuWidget != nullptr && PauseMenuViewModel != nullptr) 
		{
			PauseMenuWidget->SetViewModel(PauseMenuViewModel);
		}
	}
}