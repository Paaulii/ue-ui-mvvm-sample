// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "MVVMViewModelBase.h"
#include "VMCharacterHealth.generated.h"

class AAssigmentPlayerController;
class APlayerCharacter;
/**
 * 
 */
UCLASS()
class ASSIGNMENT_API UVMCharacterHealth : public UMVVMViewModelBase
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void SetCurrentHealth(float Health);
	void SetMaxHealth(float NewMaxHealth);
	
	UFUNCTION(BlueprintPure, FieldNotify)
	float GetHealthPercent() const;
	
	float GetCurrentHealth() const
	{
		return CurrentHealth;
	}
 
	float GetMaxHealth() const
	{
		return MaxHealth;
	}

	EHealthState GetCurrentHealthState() const
	{
		return CurrentHealthState;
	}

	EHealthState GetLastHealthState() const
	{
		return LastHealthState;
	}

	void SetModel(APlayerCharacter* PlayerController);
protected:
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, Category = "ViewModel")
	float CurrentHealth;
	
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, Category = "ViewModel")
	float MaxHealth;
	
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Category = "ViewModel")
	EHealthState LastHealthState = EHealthState::Default;
	
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Category = "ViewModel")
	EHealthState CurrentHealthState = EHealthState::Default;
	
private:
	UPROPERTY(EditDefaultsOnly)
	float LowHealthPercentageThreshold = 0.0f;
	
	float LowHealthThreshold;
	void ChangeHealthState();
};
