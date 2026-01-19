
#pragma once

#include "CoreMinimal.h"
#include "VMCharacterHealth.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"
class UVMSlotIndicator;
class UHUDViewModel;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterHealthVMCreatedSig, UVMCharacterHealth*, CharacterHealthVM);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotIndicatorVMCreatedSig, UVMSlotIndicator*, SlotIndicatorVM);

UCLASS()
class ASSIGNMENT_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void OnSetCharacterHealthViewModel(UVMCharacterHealth* CharacterHealthVM) const;
	
	void OnSetSlotIndicatorViewModel(UVMSlotIndicator* SlotIndicatorVM) const;
	
	UPROPERTY(BlueprintAssignable)
	FOnCharacterHealthVMCreatedSig OnCharacterHealthVMUpdated;

	UPROPERTY(BlueprintAssignable)
	FOnSlotIndicatorVMCreatedSig OnSlotIndicatorVMCreatedSig;
};
