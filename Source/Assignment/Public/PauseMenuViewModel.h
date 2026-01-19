#pragma once

#include "CoreMinimal.h"
#include "VMBase.h"
#include "PauseMenuViewModel.generated.h"

class AAssigmentPlayerController;
enum class EHardwareDevicePrimaryType : uint8;
enum EMouseCursor::Type : int;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShowViewSig);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHideViewSig);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnViewHiddenSig);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeCursorSig, EMouseCursor::Type, CursorType);

UCLASS()
class ASSIGNMENT_API UPauseMenuViewModel : public UVMBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void QuitGame() const;

	UFUNCTION(BlueprintCallable)
	void ReturnToGame();

	void SetModels(APlayerCharacter* PlayerCharacter, AAssigmentPlayerController* Controller);

	UPROPERTY(BlueprintAssignable)
	FOnChangeCursorSig OnChangeCursor;

	UPROPERTY(BlueprintAssignable)
	FOnShowViewSig OnShowView;

	UPROPERTY(BlueprintAssignable)
	FOnHideViewSig OnHideView;

	UPROPERTY(BlueprintAssignable)
	FOnViewHiddenSig OnViewHidden;
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Pause Menu Widget Config")
	float HidePauseMenuTimeout;
private:
	UFUNCTION()
	void TogglePauseMenu();
	void HidePauseMenu();
	void AdjustViewportPerPlatform() const;
	EHardwareDevicePrimaryType GetPlayerRecentlyUsedDeviceType() const;

	UPROPERTY()
	TObjectPtr<AAssigmentPlayerController> PlayerController = nullptr;

	bool bPauseMenuActive = false;
	bool bHidePauseMenuTimerSet = false;
	FTimerHandle HideTimer;
	FInputModeGameAndUI InputMode;
};
