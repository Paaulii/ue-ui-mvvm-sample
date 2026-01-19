
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AssigmentPlayerController.generated.h"
class UVMCharacterHealth;
class UInputMappingContext;
class UPauseMenuWidget;
class UPauseMenuViewModel;
class UWidget;
class UHUDWidget;
class UHUDViewModel;
class APlayerCharacter;
enum class EHardwareDevicePrimaryType : uint8;
enum class ESPMode : uint8;

UCLASS()
class ASSIGNMENT_API AAssigmentPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void SetGamePaused(bool bIsPaused);
	void SetPauseMenuVisible(bool bIsVisible);
	void QuitGame();
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "UI|Widget")
	TSubclassOf<UPauseMenuWidget> PauseMenuWidgetClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "UI|Widget")
	TSubclassOf<UHUDWidget> HudWidgetClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "UI|Viewmodels")
	TSubclassOf<UVMCharacterHealth> CharacterHealthViewModelClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "UI|Viewmodels")
	TSubclassOf<UPauseMenuViewModel> PauseMenuViewModelClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputMappingContext* DefaultMappingContext = nullptr;
private:
	void SetupUI();

	UPROPERTY()
	TObjectPtr<UPauseMenuWidget> PauseMenuWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UHUDWidget> HudWidget = nullptr;

	UPROPERTY()
	TObjectPtr<APlayerCharacter> PlayerCharacter = nullptr;

	UPROPERTY()
	TObjectPtr<UVMCharacterHealth> CharacterHealthViewModel = nullptr;

	UPROPERTY()
	TObjectPtr<UPauseMenuViewModel> PauseMenuViewModel = nullptr;
};
