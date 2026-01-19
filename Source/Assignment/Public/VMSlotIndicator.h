#pragma once

#include "CoreMinimal.h"
#include "VMBase.h"
#include "VMSlotIndicator.generated.h"

enum class ESlotType : uint8;
UCLASS()
class ASSIGNMENT_API UVMSlotIndicator : public UVMBase
{
	GENERATED_BODY()
public:
	virtual  void SetModel(APlayerCharacter* PlayerCharacter) override;
	
	float GetSlotsFillPercentage() const
	{
		return SlotsFillPercentage;
	}
	
	TMap<ESlotType, bool> GetSlotsActivationState() const
	{
		return SlotsActivationState;
	}
	
protected:
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, Category = "ViewModel")
	float SlotsFillPercentage = 0.0f;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, Category = "ViewModel")
	TMap<ESlotType, bool> SlotsActivationState;

	UPROPERTY(BlueprintReadOnly)
	uint8 ActiveSlotsCount = 0;
private:
	UFUNCTION()
	void OnSlotPressed(ESlotType SlotType);
	void UpdateSlotFillPercentage();
};
