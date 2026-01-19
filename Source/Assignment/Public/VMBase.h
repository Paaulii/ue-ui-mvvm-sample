#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "VMBase.generated.h"
class APlayerCharacter;

UCLASS()
class ASSIGNMENT_API UVMBase : public UMVVMViewModelBase
{
	GENERATED_BODY()
public:
	virtual void SetModel(APlayerCharacter* PlayerCharacter);
protected:
	UPROPERTY()
	TObjectPtr<APlayerCharacter> Model = nullptr;
};
