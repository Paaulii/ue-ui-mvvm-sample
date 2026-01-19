#include "VMSlotIndicator.h"

#include "Enums.h"
#include "PlayerCharacter.h"

void UVMSlotIndicator::SetModel(APlayerCharacter* PlayerCharacter)
{
	Super::SetModel(PlayerCharacter);

	if (Model == nullptr) 
	{
		return;
	}

	SlotsActivationState.Add(ESlotType::Left, false);
	SlotsActivationState.Add(ESlotType::Middle, false);
	SlotsActivationState.Add(ESlotType::Right, false);

	Model->OnSlotPressed.AddDynamic(this, &UVMSlotIndicator::OnSlotPressed);
}

void UVMSlotIndicator::OnSlotPressed(ESlotType SlotType) 
{
	if (SlotsActivationState.Contains(SlotType)) 
	{
		bool* bSlotActive = SlotsActivationState.Find(SlotType);
		*bSlotActive = !*bSlotActive;
		UpdateSlotFillPercentage();
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(SlotsActivationState);
	}
}

void UVMSlotIndicator::UpdateSlotFillPercentage()
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
