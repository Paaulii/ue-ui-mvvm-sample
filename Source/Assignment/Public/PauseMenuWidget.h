
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuWidget.generated.h"
enum EMouseCursor::Type : int;
class UVMPauseMenu;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPauseMenuViewModelUpdatedSig, UVMPauseMenu*, ViewModel);

UCLASS()
class ASSIGNMENT_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetViewModel(UVMPauseMenu* PauseMenuViewModel);
	UVMPauseMenu* ViewModel;
protected:
	UPROPERTY(BlueprintAssignable)
	FOnPauseMenuViewModelUpdatedSig OnViewModelUpdated;
};
