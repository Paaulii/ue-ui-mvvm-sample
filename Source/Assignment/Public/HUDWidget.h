
#pragma once

#include "CoreMinimal.h"
#include "VMCharacterHealth.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"
class UHUDViewModel;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterHealthVMUpdatedSig, UVMCharacterHealth*, CharacterHealthVM);

UCLASS()
class ASSIGNMENT_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetCharacterHealthViewModel(UVMCharacterHealth* CharacterHealthVM) const;
	
	UPROPERTY(BlueprintAssignable)
	FOnCharacterHealthVMUpdatedSig OnCharacterHealthVMUpdated;
};
