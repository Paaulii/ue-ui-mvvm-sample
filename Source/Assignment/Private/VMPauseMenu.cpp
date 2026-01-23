#include "VMPauseMenu.h"
#include "PlayerCharacter.h"
#include "AssigmentPlayerController.h"
#include "GameFramework/InputDeviceSubsystem.h"
#include "GameFramework/InputDeviceProperties.h"
#include "Kismet/KismetSystemLibrary.h"

void UVMPauseMenu::SetModels(APlayerCharacter* PlayerCharacter, AAssigmentPlayerController* Controller)
{
	Super::SetModel(PlayerCharacter);
	PlayerController = Controller;
	Model->OnPauseButtonPressed.AddDynamic(this, &UVMPauseMenu::TogglePauseMenu);
}

void UVMPauseMenu::TogglePauseMenu()
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
		PlayerController->GetWorldTimerManager().SetTimer(HideTimer, this, &UVMPauseMenu::HidePauseMenu, HidePauseMenuTimeout, false);
	}
}

void UVMPauseMenu::AdjustViewportPerPlatform() const
{
	EHardwareDevicePrimaryType LastUsedDevice = GetPlayerRecentlyUsedDeviceType();
	EMouseCursor::Type CursorType = LastUsedDevice == EHardwareDevicePrimaryType::KeyboardAndMouse ?
		EMouseCursor::Type::Default : EMouseCursor::Type::None;
	OnChangeCursor.Broadcast(CursorType);
}

void UVMPauseMenu::HidePauseMenu()
{
	PlayerController->SetPauseMenuVisible(false);
	bHidePauseMenuTimerSet = false;
	OnViewHidden.Broadcast();
}

void UVMPauseMenu::QuitGame() const
{
	PlayerController->QuitGame();
}

void UVMPauseMenu::ReturnToGame()
{
	TogglePauseMenu();
}

EHardwareDevicePrimaryType UVMPauseMenu::GetPlayerRecentlyUsedDeviceType() const
{
	UInputDeviceSubsystem* InputDeviceSubsystem = UInputDeviceSubsystem::Get();

	if ( PlayerController && InputDeviceSubsystem )
	{
		FHardwareDeviceIdentifier HardwareDevice = InputDeviceSubsystem->GetMostRecentlyUsedHardwareDevice(PlayerController->GetPlatformUserId());
		return HardwareDevice.PrimaryDeviceType;
	}

	return EHardwareDevicePrimaryType::Unspecified;
}