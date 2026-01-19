#include "VMCharacterHealth.h"

#include "PlayerCharacter.h"


void UVMCharacterHealth::SetCurrentHealth(float NewCurrentHealth)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(CurrentHealth, NewCurrentHealth))
	{
		ChangeHealthState();
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthPercent);
	}
}

float UVMCharacterHealth::GetHealthPercent() const
{
	if (MaxHealth != 0)
	{
		return CurrentHealth / MaxHealth;
	}
	
	return 0;
}

void UVMCharacterHealth::SetModel(APlayerCharacter* PlayerCharacter)
{
	PlayerCharacter->OnHealthChanged.AddDynamic(this, &UVMCharacterHealth::SetCurrentHealth);

	MaxHealth = PlayerCharacter->GetMaxHealth();
	CurrentHealth = PlayerCharacter->GetHealth();
	LowHealthThreshold = MaxHealth * LowHealthPercentageThreshold;
}

void UVMCharacterHealth::SetMaxHealth(float NewMaxHealth)
{	
	if (UE_MVVM_SET_PROPERTY_VALUE(MaxHealth, NewMaxHealth))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthPercent);
	}
}

void UVMCharacterHealth::ChangeHealthState()
{

	EHealthState HealthState = EHealthState::Default;

	if (CurrentHealth <= LowHealthThreshold) 
	{
		HealthState = EHealthState::LowHealth;
	}

	if (CurrentHealth <= 0) 
	{
		HealthState = EHealthState::Dead;
	}

	if (LastHealthState != HealthState) 
	{
		UE_MVVM_SET_PROPERTY_VALUE(CurrentHealthState, HealthState);
		UE_MVVM_SET_PROPERTY_VALUE(LastHealthState, HealthState);
	}
}
