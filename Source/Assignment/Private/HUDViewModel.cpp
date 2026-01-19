#include "HUDViewModel.h"
#include "PlayerCharacter.h"

void UHUDViewModel::SetModel(APlayerCharacter* PlayerCharacter)
{
	Super::SetModel(PlayerCharacter);

	if (Model == nullptr) 
	{
		return;
	}

	SlotsActivationState.Add(ESlotType::Left, false);
	SlotsActivationState.Add(ESlotType::Middle, false);
	SlotsActivationState.Add(ESlotType::Right, false);

	Model->OnHealthChanged.AddDynamic(this, &UHUDViewModel::SetHealthFillPercentage);
	Model->OnSlotPressed.AddDynamic(this, &UHUDViewModel::OnSlotPressed);

	MaxHealth = Model->GetMaxHealth();
	LowHealthTreshold = MaxHealth * LowHealthPercentageThreshold;
	SetHealthFillPercentage(Model->GetHealth());
}

void UHUDViewModel::OnSlotPressed(ESlotType SlotType) 
{
	if (SlotsActivationState.Contains(SlotType)) 
	{
		bool* bSlotActive = SlotsActivationState.Find(SlotType);
		*bSlotActive = !*bSlotActive;
		UpdateSlotFillPercentage();
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(SlotsActivationState);
	}
}

void UHUDViewModel::SetHealthFillPercentage(float Value)
{
	float Percentage = Value / MaxHealth;
	if (UE_MVVM_SET_PROPERTY_VALUE(HealthFillPercentage, Percentage))
	{
		SetHealth(Value);
		ChangeHealthState();
	}
}

void UHUDViewModel::SetHealth(float Value)
{
	UE_MVVM_SET_PROPERTY_VALUE(Health, Value);
}

void UHUDViewModel::UpdateSlotFillPercentage()
{
	uint8 SlotsNumber = SlotsActivationState.Num();
	uint8 ActiveSlots = 0;

	for (auto& Element : SlotsActivationState)
	{
		if (Element.Value == true) 
		{
			ActiveSlots++;
		}
	}

	ActiveSlotsCount = ActiveSlots;
	float Percentage = (float)ActiveSlots / (float)SlotsNumber;
	UE_MVVM_SET_PROPERTY_VALUE(SlotsFillPercentage, Percentage);
}

void UHUDViewModel::ChangeHealthState()
{
	EHealthState HealthState = EHealthState::Default;

	if (Health <= LowHealthTreshold) 
	{
		HealthState = EHealthState::LowHealth;
	}

	if (Health <= 0) 
	{
		HealthState = EHealthState::Dead;
	}

	if (LastHealthState != HealthState) 
	{
		OnChangeHealthState.Broadcast(LastHealthState, HealthState);
		LastHealthState = HealthState;
	}
}
