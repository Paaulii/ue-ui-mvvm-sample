#include "PauseMenuViewModel.h"
#include "PlayerCharacter.h"
#include "AssigmentPlayerController.h"
#include "GameFramework/InputDeviceSubsystem.h"
#include "GameFramework/InputDeviceProperties.h"
#include "Kismet/KismetSystemLibrary.h"

void UPauseMenuViewModel::SetModels(APlayerCharacter* PlayerCharacter, AAssigmentPlayerController* Controller)
{
	Super::SetModel(PlayerCharacter);
	PlayerController = Controller;
	Model->OnPauseButtonPressed.AddDynamic(this, &UPauseMenuViewModel::TogglePauseMenu);
}

void UPauseMenuViewModel::TogglePauseMenu()
{
	if (bHidePauseMenuTimerSet) 
	{
		return;
	}

	bPauseMenuActive = !bPauseMenuActive;
	if (bPauseMenuActive)
	{
		OnShowView.Broadcast();
		PlayerController->SetPauseMenuVisible(true);
		AdjustViewportPerPlatform();
		PlayerController->SetGamePaused(true);
	}
	else 
	{
		PlayerController->SetGamePaused(false);
		bHidePauseMenuTimerSet = true;
		OnHideView.Broadcast();
		PlayerController->GetWorldTimerManager().SetTimer(HideTimer, this, &UPauseMenuViewModel::HidePauseMenu, HidePauseMenuTimeout, false);
	}
}

void UPauseMenuViewModel::AdjustViewportPerPlatform() const
{
	EHardwareDevicePrimaryType LastUsedDevice = GetPlayerRecentlyUsedDeviceType();
	EMouseCursor::Type CursorType = LastUsedDevice == EHardwareDevicePrimaryType::KeyboardAndMouse ?
		EMouseCursor::Type::Default : EMouseCursor::Type::None;
	OnChangeCursor.Broadcast(CursorType);
}

void UPauseMenuViewModel::HidePauseMenu()
{
	PlayerController->SetPauseMenuVisible(false);
	bHidePauseMenuTimerSet = false;
	OnViewHidden.Broadcast();
}

void UPauseMenuViewModel::QuitGame() const
{
	PlayerController->QuitGame();
}

void UPauseMenuViewModel::ReturnToGame()
{
	TogglePauseMenu();
}

EHardwareDevicePrimaryType UPauseMenuViewModel::GetPlayerRecentlyUsedDeviceType() const
{
	UInputDeviceSubsystem* InputDeviceSubsystem = UInputDeviceSubsystem::Get();

	if ( PlayerController && InputDeviceSubsystem )
	{
		FHardwareDeviceIdentifier HardwareDevice = InputDeviceSubsystem->GetMostRecentlyUsedHardwareDevice(PlayerController->GetPlatformUserId());
		return HardwareDevice.PrimaryDeviceType;
	}

	return EHardwareDevicePrimaryType::Unspecified;
}