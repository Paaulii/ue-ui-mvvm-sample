#include "HUDWidget.h"

void UHUDWidget::OnSetCharacterHealthViewModel(UVMCharacterHealth* CharacterHealthVM) const
{
	OnCharacterHealthVMUpdated.Broadcast(CharacterHealthVM);
}

void UHUDWidget::OnSetSlotIndicatorViewModel(UVMSlotIndicator* SlotIndicatorVM) const
{
	OnSlotIndicatorVMCreatedSig.Broadcast(SlotIndicatorVM);
}
