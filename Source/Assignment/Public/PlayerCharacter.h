#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enums.h"
#include "PlayerCharacter.generated.h"
class UInputAction;
enum class EHealthIncrementMode : uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPauseButtonPressedSig);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotPressedSig, ESlotType, Type);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSig, float, Value);

UCLASS()
class ASSIGNMENT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	float GetHealth() const
	{
		return Health;
	}

	float GetMaxHealth() const
	{
		return MaxHealth;
	}

	UPROPERTY(BlueprintAssignable)
	FOnHealthChangedSig OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnSlotPressedSig OnSlotPressed;

	UPROPERTY(BlueprintAssignable)
	FPauseButtonPressedSig OnPauseButtonPressed;

protected:
	virtual void PostInitializeComponents() override;

	UPROPERTY(BlueprintReadOnly)
	float Health = 0.0f;

	UPROPERTY(EditDefaultsOnly)
	float HealthIncrementValue = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxHealth = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* PauseAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* ChangeHealthAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* LeftSlotActivateAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* MiddleSlotActivateAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* RightSlotActivateAction;

private:
	void PauseActionButtonPressed();
	void HandleLeftSlotActivation();
	void HandleMiddleSlotActivation();
	void HandleRightSlotActivation();
	void ChangeHealth();

	EHealthIncrementMode IncrementMode;
};
