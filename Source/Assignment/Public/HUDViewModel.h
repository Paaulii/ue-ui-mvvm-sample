#pragma once

#include "CoreMinimal.h"
#include "VMBase.h"
#include "Enums.h"
#include "HUDViewModel.generated.h"

class APlayerCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChangeHealthState, EHealthState, LastHealthState, EHealthState, NewHealthState);

UCLASS()
class ASSIGNMENT_API UHUDViewModel : public UVMBase
{
	GENERATED_BODY()
public: 
	void SetModel(APlayerCharacter* PlayerCharacter) override;

	UPROPERTY(BlueprintAssignable)
	FOnChangeHealthState OnChangeHealthState;

protected:
	UPROPERTY(BlueprintReadOnly, FieldNotify, Setter, Category = "ViewModel")
	float HealthFillPercentage = 0.0f;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Category = "ViewModel")
	float SlotsFillPercentage = 0.0f;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Setter, Category = "ViewModel")
	float Health = 0.0f;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Category = "ViewModel")
	TMap<ESlotType, bool> SlotsActivationState;

	UPROPERTY(BlueprintReadOnly)
	uint8 ActiveSlotsCount = 0;

	UPROPERTY(EditDefaultsOnly)
	float LowHealthPercentageThreshold = 0.0f;
private:
	UFUNCTION()
	void SetHealthFillPercentage(float Value);

	UFUNCTION()
	void SetHealth(float Value);

	UFUNCTION()
	void OnSlotPressed(ESlotType SlotType);

	void UpdateSlotFillPercentage();
	void ChangeHealthState();
	float MaxHealth = 0.0f;
	float LowHealthTreshold = 0.0f;
	EHealthState LastHealthState = EHealthState::Default;
};
